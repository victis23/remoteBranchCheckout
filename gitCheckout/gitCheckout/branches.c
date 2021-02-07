//
//  branches.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/11/21.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "branches.h"
#include "scripts.h"

#define MAX_BUFF_CAP 1500

//Could have used sprintf but wanted to have an example of snprintf.
void findAndCheckoutBranch(const char *searchTerm) {
	char buffer[MAX_BUFF_CAP];
	snprintf(buffer, sizeof(buffer), "#/bin/bash\nremotes=%s\n%s", searchTerm, checkoutScript);
	
	system(buffer);
}
