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

#define SEARCH_RESULT_BRANCHES_MAX 100
#define COMMAND_MAX_LEN 300
#define REBASE_COMMAND_MAX_LEN 1500
#define BRANCH_NAME_MAX_LEN 1000


void startRebasingProcess() {
	rollBackCommitHead();
}

void rollBackCommitHead() {
	system(resetStash);
	printf("How far back would you like to permanently reset this branch's head?\n");
	
	int rollBackAmount;
	scanf("%d", &rollBackAmount);
	
	char *resetCommand = malloc(COMMAND_MAX_LEN * sizeof(char));
	sprintf(resetCommand, "git reset HEAD~%d --hard", rollBackAmount);
	system(resetCommand);
	
	attemptRebase(findBranchToRebaseWith());
	
	printf("Would you like to apply a patch to your newly rebased branch? ('y'/'n')\n");
	char* shouldApplyPatch = malloc(sizeof(char));
	scanf("%s", shouldApplyPatch);
	
	if (strcmp(shouldApplyPatch, "y") == 0) {
		reapplyStashedChanges();
	}
	
	free(resetCommand);
	free(shouldApplyPatch);
}

char* findBranchToRebaseWith() {
	char *branchSearchCommand = malloc(COMMAND_MAX_LEN * sizeof(char));
	char *searchTerm = (char *) malloc(COMMAND_MAX_LEN * sizeof(char));
	
	printf("Enter search term: ");
	scanf("%s", searchTerm);
	sprintf(branchSearchCommand, "git branch -a | grep %s", searchTerm);

	system("git fetch");
	FILE *listOfBranches = NULL;
	listOfBranches = popen(branchSearchCommand, "r");

	int character;
	int characterCountPerBranch = 0;
	int branchCount = 0;
	char branches[SEARCH_RESULT_BRANCHES_MAX][BRANCH_NAME_MAX_LEN];
	char branch[BRANCH_NAME_MAX_LEN];
	
	while ((character = fgetc(listOfBranches)) != EOF) {
		if (characterCountPerBranch == 0) {
			printf("%d ", branchCount);
		}
		
		if (character == '*') {
			character = ' ';
		}
		
		branch[characterCountPerBranch] = character;
		characterCountPerBranch++;
		
		if (character == '\n' && branchCount < SEARCH_RESULT_BRANCHES_MAX) {
			strcpy(branches[branchCount], branch);
			
			branchCount++;
			memset(branch, '\0', sizeof(branch));
			characterCountPerBranch = 0;
		} else if (branchCount >= SEARCH_RESULT_BRANCHES_MAX) {
			fprintf(stderr, "Search has exceeded %d - Which is the maximum amount of results allowed.\n",SEARCH_RESULT_BRANCHES_MAX);
		}
		
		printf("%c",character);
	}
	
	if (branchCount < 1) {
		fprintf(stderr,"No branches were found for this search term. \n");
		exit(0);
	}

	printf("Please select a branch (0 - %d): ", branchCount - 1);
	int branchSelection;
	scanf("%d", &branchSelection);
	
	char *selectedBranch = branches[branchSelection];
	
	pclose(listOfBranches);
	free(searchTerm);
	free(branchSearchCommand);
	
	printf("\nProcessing... \n");
	
	return selectedBranch;
}

// Just wanted to test out calloc and the type casting...
void attemptRebase(char *branchName) {
	char *rebaseCommand = (char *) calloc(REBASE_COMMAND_MAX_LEN, sizeof(char));
	sprintf(rebaseCommand, "git rebase %s", branchName);
	system(rebaseCommand);
	free(rebaseCommand);
}

void reapplyStashedChanges(void) {
	applyStash();
}
