//
//  commits.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scripts.h"
#include "commits.h"

void commitChanges() {
	system(commit);
}

void commitAndPush() {
	commitChanges();
	system(push);
}

void applyPatchAsCommit(int position, char *message) {
	char instruction[1000];
	char commands[1000] = "git stash apply stash@{%d}; git add .; git commit -m \"%s\"";
	sprintf(instruction, commands,position, message);
	
	system(instruction);
}

void amendAndPush() {
	system(quickAmend);
	system(pushWithForce);
}

void amend() {
	system(quickAmend);
}
