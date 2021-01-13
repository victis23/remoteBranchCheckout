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
		exit(1);
	}
	
	char patchedCommand[100];
	sprintf(patchedCommand, ap2, c+1);
	
	FILE *returned = NULL;
	char *patchContainer = (char *) malloc(5000);
	returned = popen(patchedCommand, "r");
	if (returned == NULL) {
		printf("Nothing was saved to file.\n");
	} else {
		
		while (fgets(patchContainer, 5000, returned)) {
			printf("%s",patchContainer);
		}
		
		char *patchInfo = strdup(patchContainer);
		
		int index = 0;
		int colonCounter = 0;
		unsigned long length = strlen(patchInfo);
		
		while (index < length) {
			if (*patchInfo == ':') {
				colonCounter++;
				patchInfo = patchInfo + 2;
			}
			
			if (colonCounter >= 2) {
				break;
			}
			
			patchInfo++;
			index++;
		}
		
		printf("Message: %s",patchInfo);
		applyPatchAsCommit(c, patchInfo);
	}
	pclose(returned);
	free(patchContainer);
}
