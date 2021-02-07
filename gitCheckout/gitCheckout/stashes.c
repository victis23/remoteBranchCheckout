//
//  stashes.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scripts.h"
#include "stashes.h"
#include "commits.h"

#define READ_OP "r"
#define PATCH_COMMAND_MAX_LEN 100
#define PATCH_MSG_MAX_LEN 5000
#define MAX_COLONS 2

void stashChanges() {
	system(stash);
}

void resetHeadAndStash() {
	system(resetStash);
}

void applyStash() {
	system(ap1);
	
	FILE *stashList = NULL;
	stashList = popen(ap1, READ_OP);
	
	int v;
	int count = 0;
	while ((v = fgetc(stashList)) != EOF) {
		if (v == '\n')
			count++;
	}
	
	pclose(stashList);
	
	printf("Please select stash index (0 - %d)\n", count - 1);
	int c = 0;
	scanf("%d",&c);
	
	if (!(c >= 0 && c <= count - 1)) {
		fprintf(stderr,"Invalid Entry\n");
		exit(1);
	}
	
	char patchedCommand[PATCH_COMMAND_MAX_LEN];
	sprintf(patchedCommand, ap2, c+1);
	
	FILE *returnedPatch = NULL;
	returnedPatch = popen(patchedCommand, "r");
	
	char *patchMsg = (char *) malloc(PATCH_MSG_MAX_LEN * sizeof(char));
	
	if (returnedPatch == NULL) {
		fprintf(stderr,"Nothing was saved to file.\n");
	} else {
		
		while (fgets(patchMsg, PATCH_MSG_MAX_LEN, returnedPatch)) {
			printf("%s",patchMsg);
		}
		
		char *patchMsgPtr_Duplicate = strdup(patchMsg);
		
		int index = 0;
		int colonCounter = 0;
		unsigned long patchMsg_stdoutLength = strlen(patchMsgPtr_Duplicate);
		
		while (index < patchMsg_stdoutLength) {
			if (*patchMsgPtr_Duplicate == ':') {
				colonCounter++;
				patchMsgPtr_Duplicate = patchMsgPtr_Duplicate + 2;
			}
			
			if (colonCounter >= MAX_COLONS) {
				break;
			}
			
			patchMsgPtr_Duplicate++;
			index++;
		}
		
		printf("Message: %s",patchMsgPtr_Duplicate);
		applyPatchAsCommit(c, patchMsgPtr_Duplicate, PATCH_MSG_MAX_LEN);
	}
	
	pclose(returnedPatch);
	free(patchMsg);
}
