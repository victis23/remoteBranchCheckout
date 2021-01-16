//
//  rebase.h
//  gitCheckout
//
//  Created by Scott Leonard on 1/31/21.
//

#ifndef rebase_h
#define rebase_h

#include <stdio.h>
#include <stdlib.h>

char* branchName;
void startRebasingProcess(void);
void rollBackCommitHead(void);
char* findBranchToRebaseWith(void);
void attemptRebase(char *branchName);
void reapplyStashedChanges(void);
#endif /* rebase_h */
