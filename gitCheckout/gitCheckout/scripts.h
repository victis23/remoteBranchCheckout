//
//  script.h
//  gitCheckout
//
//  Created by Scott Leonard on 1/10/21.
//

#ifndef scripts_h
#define scripts_h

char checkoutScript[1200];
char quickAmend[200];
char commit[200];
char resetStash[500];
char ap1[50];
char ap2[50];

int applyPatchAsCommit(int position, char *message);

#endif /* script_h */
