#!/bin/bash

DIFF=$(diff $1 $2) 
if [ "$DIFF" == "" ] 
then
    echo -e "\033[0;32mOK\033[0m"
else
	echo -e "\033[0;31mFAILED\033[0m"
	echo $DIFF
fi