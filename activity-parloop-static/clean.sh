#!/bin/sh

# remove job out and error files
if  ls *.sh.* 1> /dev/null 2>&1; 
then
    rm *.sh.*
fi

# remove *.o files
if ls *.o 1> /dev/null 2>&1;
then
    rm *.o
fi
