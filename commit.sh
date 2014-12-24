#!/bin/sh
git add .
echo -n "Enter commit message:"
read message
if test -z "$message" ; then
	message="no message"
fi
git commit -a -m "$message"
git push origin master
