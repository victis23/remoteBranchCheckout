//
//  main.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/9/21.
//

#include <stdio.h>
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
// -rebase: Allows user to reset branch head and rebase to remote or local branches.

#define AMEND "-a"
#define AMEND_AND_PUSH "-ap"
#define COMMIT_AND_PUSH "-c"
#define COMMIT_CHANGES "-commit"
#define RESET_HEAD_AND_STASH "-rs"
#define APPLY_STASH "-apply"
#define STASH_CHANGES "-stash"
#define START_REBASE "-rebase"
#define MIN_ARGS 1
#define MAX_ARGS 3

int main(int argc, const char * argv[]) {
	
	char *primaryUserInputCommand = (char *) argv[1];
	
	if (argc > MIN_ARGS && argc < MAX_ARGS) {
		if (strcmp(primaryUserInputCommand, AMEND) == 0) {
			amend();
		} else if (strcmp(primaryUserInputCommand, AMEND_AND_PUSH) == 0) {
			amendAndPush();
		} else if (strcmp(primaryUserInputCommand, COMMIT_AND_PUSH) == 0) {
			commitAndPush();
		} else if (strcmp(primaryUserInputCommand, COMMIT_CHANGES) == 0) {
			commitChanges();
		} else if (strcmp(primaryUserInputCommand, RESET_HEAD_AND_STASH) == 0) {
			resetHeadAndStash();
		} else if (strcmp(primaryUserInputCommand, APPLY_STASH) == 0) {
			applyStash();
		} else if (strcmp(primaryUserInputCommand, STASH_CHANGES) == 0) {
			stashChanges();
		} else if (strcmp(primaryUserInputCommand, START_REBASE) == 0) {
			startRebasingProcess();
		} else {
			findAndCheckoutBranch(primaryUserInputCommand);
		}
	} else if (argc >= MAX_ARGS) {
		invalidEntry();
	} else {
		introductionWarning();
	}
	
	return 0;
}
