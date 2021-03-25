#!/bin/bash

function test_time {
    # compare 
    if [[ ! $1 =~ $sci_notation_regex ]] ; 
    then
        echo ERROR: time is not on stderr or not formatted properly
        echo
        rm .time
        exit 1
    fi

    # delete tmp file 
    rm .time
}

if [ ! -f "./main" ]; then
  echo -e "\nERROR!\nUnable to test!\nYou must compile first with \"make\""
  exit 1
fi

if [ -f ".passed" ]; then
  rm .passed
fi

# testing the
./main test_sources.txt the 1000000 > test.txt 2> .time
test=`cat test.txt`;
if [ ${test} -ne 40368 ]; then
  echo -e "Test Failed: expected \"the\" to equal 40368 but got ${test}"
  rm test.txt
  rm .time
  exit 1
fi
rm test.txt

# testing a
./main test_sources.txt a 1000000 > test.txt 2> .time
test=`cat test.txt`;
if [ ${test} -ne 16008 ]; then
  echo -e "Test Failed: expected \"a\" to equal 16008 but got ${test}"
  rm test.txt
  rm .time
  exit 1
fi
rm test.txt

# testing an
./main test_sources.txt an 1000000 > test.txt 2> .time
test=`cat test.txt`;
if [ ${test} -ne 1344 ]; then
  echo -e "Test Failed: expected \"an\" to equal 1344 but got ${test}"
  rm test.txt
  rm .time
  exit 1
fi
rm test.txt

# check time format
test_time $(cat .time)

touch .passed

# all tests passed
echo ================================
echo
echo Success! All tests passed! ":)"
