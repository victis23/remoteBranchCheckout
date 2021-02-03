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

void findAndCheckoutBranch(const char *searchTerm) {
	char buffer[1500];
	snprintf(buffer, sizeof(buffer), "#/bin/bash\nremotes=%s\n%s", searchTerm, checkoutScript);
	
	system(buffer);
}
