//
//  rebase.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/31/21.
//

#include "rebase.h"
#include "scripts.h"
#include "stashes.h"
#include <string.h>


void startRebasingProcess() {
	rollBackCommitHead();
}

void rollBackCommitHead() {
	system(resetStash);
	printf("How far back would you like to permanently reset this branch's head?\n");
	
	int rollBackAmount;
	scanf("%d", &rollBackAmount);
	
	char *resetCommand = malloc(100);
	sprintf(resetCommand, "git reset HEAD~%d --hard", rollBackAmount);
	system(resetCommand);
	
	attemptRebase(findBranchToRebaseWith());
	
	printf("Would you like to apply your latest patch? ('y'/'n')\n");
	char* shouldApplyPatch = malloc(sizeof(char));
	scanf("%s", shouldApplyPatch);
	
	if (strcmp(shouldApplyPatch, "y") == 0) {
		reapplyStashedChanges();
	}
	
	free(resetCommand);
	free(shouldApplyPatch);
}

char* findBranchToRebaseWith(void) {
	char *gitBranchList = malloc(200);
	char *searchTerm = (char *) malloc(100);
	
	printf("Enter search term: ");
	scanf("%s", searchTerm);
	sprintf(gitBranchList, "git branch -a | grep %s", searchTerm);

	system("git fetch");
	FILE *listOfBranches = NULL;
	listOfBranches = popen(gitBranchList, "r");

	int character;
	int characterCountPerBranch = 0;
	int branchCount = 0;
	char branches[100][1000];
	char branch[1000];
	
	while ((character = fgetc(listOfBranches)) != EOF) {
		if (characterCountPerBranch == 0) {
			printf("%d ", branchCount);
		}
		
		if (character == '*') {
			character = ' ';
		}
		
		branch[characterCountPerBranch] = character;
		characterCountPerBranch++;
		
		if (character == '\n') {
			strcpy(branches[branchCount], branch);
			
			branchCount++;
			memset(branch, '\0', sizeof(branch));
			characterCountPerBranch = 0;
		}
		
		printf("%c",character);
	}
	
	if (branchCount < 1) {
		printf("No branches were found for this search term. \n");
		exit(0);
	}

	printf("Please select a branch (0 - %d): ", branchCount - 1);
	int branchSelection;
	scanf("%d", &branchSelection);
	
	char *selectedBranch = branches[branchSelection];
	
	pclose(listOfBranches);
	free(searchTerm);
	free(gitBranchList);
	
	printf("\nProcessing... \n");
	
	return selectedBranch;
}

// Just wanted to test out calloc and the type casting...
void attemptRebase(char *branchName) {
	char *rebaseCommand = (char *) calloc(1025, sizeof(char));
	sprintf(rebaseCommand, "git rebase %s", branchName);
	system(rebaseCommand);
	free(rebaseCommand);
}

void reapplyStashedChanges(void) {
	applyStash();
}
