#!/bin/bash

if [ "$#" != "1" ]; then
	echo "Empty <commit mesage>"
	echo "Usage: $0 <commit message>"
	exit
fi
git add .
git commit -m "$1"
git push origin master
