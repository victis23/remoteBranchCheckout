//
//  warnings.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/11/21.
//

#include "warnings.h"

#define STYLE_BOLD "\033[1m"
#define REG_FONT "\033[22m"

void invalidEntry() {
	printf("\nERROR: Not a valid command entry.\n");
}

void introductionWarning() {
	printf("\n%sERROR: No command was entered.%s\n\n",STYLE_BOLD,REG_FONT);
	printf("\
Common use: \n\
gitmaster <name of branch>: This will query all branches in the repo and return a list of available branches to checkout.\n\n\
Operators:\n\
-a : Amend existing commit on current branch. \n\
-ap: Amend latest commit with current changes, and pushes to remote branch.\n\
-apply : Applies selected patch as a commit with same name as patch description. \n\
-c: Creates a new commit with current changes, and entered description and pushes to remote branch. \n\
-commit: Creates commit from current changes with provided description. \n\
-rs: Resets branch head by nth amount, and stashes changes with description text entered.\n\
-rebase: Allows user to reset branch head and rebase to remote or local branches. \n\
-stash: Creates stash with provided name of current changes. \n\
\n\n\
%sNot entering a search term or operator will result in an error.%s\n\n",STYLE_BOLD,REG_FONT);
}
