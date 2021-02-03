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

void stashChanges() {
	system(stash);
}

void resetHeadAndStash() {
	system(resetStash);
}

void applyStash() {
	system(ap1);
	
	FILE *stashList = NULL;
	stashList = popen(ap1, "r");
	
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
		printf("Invalid Entry\n");
		exit(1);
	}
	
	char patchedCommand[100];
	sprintf(patchedCommand, ap2, c+1);
	
	FILE *returned = NULL;
	returned = popen(patchedCommand, "r");
	
	char *patchMsg = (char *) malloc(5000);
	
	if (returned == NULL) {
		printf("Nothing was saved to file.\n");
	} else {
		
		while (fgets(patchMsg, 5000, returned)) {
			printf("%s",patchMsg);
		}
		
		char *patchMsgDuplicate = strdup(patchMsg);
		
		int index = 0;
		int colonCounter = 0;
		unsigned long length = strlen(patchMsgDuplicate);
		
		while (index < length) {
			if (*patchMsgDuplicate == ':') {
				colonCounter++;
				patchMsgDuplicate = patchMsgDuplicate + 2;
			}
			
			if (colonCounter >= 2) {
				break;
			}
			
			patchMsgDuplicate++;
			index++;
		}
		
		printf("Message: %s",patchMsgDuplicate);
		applyPatchAsCommit(c, patchMsgDuplicate);
	}
	
	pclose(returned);
	free(patchMsg);
}
