#!/bin/bash

echo "Please do it by yourself"
echo "Command;"

echo "git add ."
echo "git commit -m <message>"
echo "git push origin master"
echo ""
exit

if [ "$#" != "1" ]; then
	echo "Empty <commit mesage>"
	echo "Usage: $0 <commit message>"
	exit
fi

git add .
git commit -m "$1"
git push origin master
