#!/bin/bash

remotes=$1

function make_selection {
local branchName=$1
echo The selected branch was ${branchName}
echo "Do you wish to checkout this branch? (y/n)"
read isCheckoutBranch
 
 if [ $isCheckoutBranch == 'y' ] || [ $isCheckoutBranch == 'n' ]; then
 case $isCheckoutBranch in
 
 'y')
 git checkout --track $branchName
 ;;
 
 'n')
 echo No action will be taken.
 ;;
 
 esac
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
echo Which branch would you like to select? "(1 - " $lineCount")"
read lineSelection
echo User selection was $lineSelection
branch=$(sed -n ${lineSelection}p <<< "$list")
make_selection $branch
elif [ -n "$list" ] && [ $lineCount -eq 1 ]
then

echo "Only one branch was found:"
echo $list
make_selection $list

# Do you wish to checkout this branch? (y/n)"
#	read isCheckoutBranch

#	if [ $isCheckoutBranch == 'y' ] || [ $isCheckoutBranch == 'n' ]; then
#		case $isCheckoutBranch in 
		
#		'y')
#		git checkout --track $list
#		;;
		
#		'n')
#		echo No action will be taken.
#		;;
		
#		esac
#	fi
else
	echo No branch found.
fi
