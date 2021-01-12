//
//  commits.h
//  gitCheckout
//
//  Created by Scott Leonard on 1/11/21.
//

#ifndef commits_h
#define commits_h

#include <stdio.h>

void commitChanges(void);
void commitAndPush(void);
void applyPatchAsCommit(int position, char *message);
void amendAndPush(void);
void amend(void);

#endif /* commits_h */
