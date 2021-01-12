//
//  script.c
//  gitCheckout
//
//  Created by Scott Leonard on 1/10/21.
//

#include <stdio.h>
#include "scripts.h"
#include <stdlib.h>

char checkoutScript[1200] = "\
function make_selection { \n\
local branchName=$1 \n\
echo The selected branch was: ${branchName} \n\
echo \"Do you wish to checkout this branch? (y/n)\" \n\
read isCheckoutBranch \n\
if [ $isCheckoutBranch == 'y' ] || [ $isCheckoutBranch == 'n' ]; then \n\
case $isCheckoutBranch in \n\
'y') \n\
if [[ \"$branchName\" =~ .*\"remote\".* ]]; then \n\
git checkout --track $branchName \n\
else \n\
git checkout $branchName \n\
fi \n\
;; \n\
'n') \n\
echo No action will be taken. \n\
;; \n\
esac \n\
else \n\
printf \"Please enter either \"y\" or \"n\", thank you.\\n\" \n\
fi \n\
} \n\
git fetch \n\
sleep 2 \n\
list=$(git branch -a | grep $remotes) \n\
echo\n\
if [ -n \"$list\" ];then \n\
echo These are the branches returned: \n\
echo \"${list}\" \n\
fi \n\
lineCount=$(echo \"$list\" | wc -l ) \n\
if [ -n \"$list\" ] && [ $lineCount -gt 1 ]; then \n\
echo Which branch would you like to select? \"(1 -\"$lineCount\")\" \n\
read lineSelection \n\
branch=$(sed -n ${lineSelection}p <<< \"$list\"); \n\
if [[ \"$branch\" =~ .*\"*\".* ]]; then \n\
echo You are already on this branch.\n\
else \n\
make_selection $branch \n\
fi \n\
elif [ -n \"$list\" ] && [ $lineCount -eq 1 ] \n\
then \n\
echo \"Only one branch was found:\"\n\
echo $list \n\
make_selection $list \n\
else \n\
echo No branch found. \n\
fi \n\
";

char quickAmend[200] = "\
#/bin/bash \n\
git add . \n\
git commit --amend \n\
";

char *pushWithForce = "git push --force-with-lease";

char commit[200] = "\
#/bin/bash \n\
printf \"Enter your commit message: \" \n\
read commitMessage; message=$commitMessage\n\
git add . \n\
git commit -m \"$message\" \n\
";

char *push = "sleep 1; git push";

char *stash = "\
echo Enter stash description: \n\
read message \n\
stashDescription=$message \n\
git stash save \"${message}\" \n\
sleep 2 \n\
git stash list \n\
";

char resetStash[500] = "\
#/bin/bash \n\
printf \"Reset branch head by (#): \" \n\
read amount \n\
re='^[0-9]+$' \n\
if [[ $amount =~ $re ]]; then \n\
resetAmount=$amount \n\
git reset HEAD~${resetAmount} --soft \n\
echo Enter stash description: \n\
read message \n\
stashDescription=$message \n\
git stash save \"${message}\" \n\
sleep 2 \n\
git stash list \n\
else \n\
echo Error: Not Numeric \n\
fi \n\
";

char ap1[50] = "\
#/bin/bash \n\
git stash list \n\
";

char ap2[50] = "git stash list | sed -n '%d p'";



