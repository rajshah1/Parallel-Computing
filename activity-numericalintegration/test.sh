#!/bin/bash

# does not account for neg numbers
sci_notation_regex='^[0-9]+([.][0-9]+)?(e[0-9]+|e-[0-9]+)?$'

function test_time {
    # compare 
    if [[ $1 =~ $sci_notation_regex ]] ; 
    then
        echo time properly formatted 
    else
        echo ERROR: time is not on stderr or not formatted properly
        echo
        rm time
        exit 1
    fi
    # delete tmp file 
    rm time
}


# tests 4 funcs, 2 N, 4 inten, 
FUNC="1 2 3 4"
NS="10000 1000000"
INTENSITIES="1 100"


# exhaust test cases
while read test; 
do

t=($test)
# correctness
ANSW=$(./main ${t[0]} 0 10 ${t[1]} ${t[2]} 2> time)  
if ./approx ${ANSW} ${t[3]};
then
    echo correct 
# check time format
    test_time $(cat time)

else # display error and quit
    echo FAIL: "./main ${t[0]} 0 10 ${t[1]} ${t[2]}" should give roughly "${t[3]}" not ${ANSW}
    exit 1
fi

done < test_cases.txt

touch .passed

# all tests passed
echo ================================
echo
echo SUCCESS! All Tests passed! ":)"
