#!/bin/bash

remotes=$1

function make_selection {
local branchName=$1
echo The selected branch was: ${branchName}
echo "Do you wish to checkout this branch? (y/n)"
read isCheckoutBranch
 
 if [ $isCheckoutBranch == 'y' ] || [ $isCheckoutBranch == 'n' ]; then

 case $isCheckoutBranch in
 'y')
 if [[ "$branchName" =~ .*"remote".* ]]; then
 git checkout --track $branchName
 else
 git checkout $branchName
 fi
 ;;
 'n')
 echo No action will be taken.
 ;;
 esac
else
printf "Please enter either \"y\" or \"n\", thank you.\n"
 fi
}

list=$(git branch -a | grep $remotes) 

echo

if [ -n "$list" ];then
echo These are the branches returned:
echo "${list}"
fi

lineCount=$(echo "$list" | wc -l )
 
if [ -n "$list" ] && [ $lineCount -gt 1 ]; then
echo Which branch would you like to select? "(1 -"$lineCount")"
read lineSelection
branch=$(sed -n ${lineSelection}p <<< "$list")
if [[ "$branch" =~ .*"*".* ]]; then
echo You are already on this branch.
else
make_selection $branch
fi
elif [ -n "$list" ] && [ $lineCount -eq 1 ]
then

echo "Only one branch was found:"
echo $list
make_selection $list

else
	echo No branch found.
fi
