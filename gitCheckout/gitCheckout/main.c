//
//  main.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scripts.h"
#include "stashes.h"
#include "commits.h"
#include "branches.h"
#include "warnings.h"
#include "rebase.h"

/* Command Argument keys */
// -a : Amend existing commit on current branch.
// -ap : Amend existing commit on current branch and push with force.
// -apply : Applies selected patch as a commit with same name as patch description.
// -c : Create a new commit with message & push to remote.
// -commit: Creates commit from current changes with provided description.
// -rs : Resets head by nth amount, and stashes changes with provided text description.
// -stash: Creates stash with provided name of current changes.
// -rebase:

int main(int argc, const char * argv[]) {
	
	char *arg1 = (char *) argv[1];
	
	if (argc > 1 && argc < 3) {
		if (strcmp(arg1, "-a") == 0) {
			amend();
		} else if (strcmp(arg1, "-ap") == 0) {
			amendAndPush();
		} else if (strcmp(arg1, "-c") == 0) {
			commitAndPush();
		} else if (strcmp(arg1, "-commit") == 0) {
			commitChanges();
		} else if (strcmp(arg1, "-rs") == 0) {
			resetHeadAndStash();
		} else if (strcmp(arg1, "-apply") == 0) {
			applyStash();
		} else if (strcmp(arg1, "-stash") == 0) {
			stashChanges();
		} else if (strcmp(arg1, "-rebase") == 0) {
			startRebasingProcess();
		} else {
			findAndCheckoutBranch(arg1);
		}
	} else if (argc >= 3) {
		invalidEntry();
	} else {
		introductionWarning();
	}
	
	return 0;
}
