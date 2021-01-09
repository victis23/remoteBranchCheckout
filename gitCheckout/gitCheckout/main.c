//
//  main.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "scripts.h"
#include <string.h>
/* Command Argument keys */
// -rs : Resets head by nth amount, and stashes changes with provided text description.
// -a : Amend existing commit on current branch.
// -c : Create a new commit with message & push to remote.
// -ap : Applies selected patch as a commit with same name as patch description.

#define STYLE_BOLD "\033[1m"
#define REG_FONT "\033[22m"

int main(int argc, const char * argv[]) {
	
	char *arg1 = (char *) argv[1];
	
	if (argc > 1 && argc < 3) {
		if (strcmp(arg1, "-a") == 0) {
			system(quickAmend);
		} else if (strcmp(arg1, "-c") == 0) {
			char newCommand[200];
			sprintf(newCommand,commit,argv[2]);
			system(newCommand);
		} else if (strcmp(arg1, "-rs") == 0) {
			system(resetStash);
		} else if (strcmp(arg1, "-ap") == 0) {
			system(ap1);
			
			printf("Please select stash index (#)\n");
			int c = 0;
			scanf("%d",&c);
						
			char patchedCommand[100];
			sprintf(patchedCommand, ap2, c+1);
			
			FILE *returned;
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
		} else {
			char buffer[1500];
			snprintf(buffer, sizeof(buffer), "#/bin/bash\nremotes=%s\n%s", arg1, checkoutScript);
			system(buffer);
		}
	} else if (argc >= 3) {
		printf("\nERROR: Not a valid command entry.\n");
	} else {
		printf("\n%sERROR: No command was entered.%s\n\n",STYLE_BOLD,REG_FONT);
		printf("\
Common use: \n\
gitmaster <name of branch>: This will query all branches in the repo and return a list of available branches to checkout.\n\n\
Operators:\n\
-rs: Resets branch head by nth amount, and stashes changes with description text entered.\n\
-a: Amend latest commit with current changes, and pushes to remote branch.\n\
-ap : Applies selected patch as a commit with same name as patch description. \n\
-c: Creates a new commit with current changes, and entered description and pushes to remote branch. \n\
\n\n\
%sNot entering a search term or operator will result in an error.%s\n\n",STYLE_BOLD,REG_FONT);
	}
	
	return 0;
}
