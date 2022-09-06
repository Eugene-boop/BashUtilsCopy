#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""

for var1 in -v -c -l -n -h -o
do
  for var2 in -v -c -l -n -h -o
  do
    if [ $var1 != $var2 ]
    then
      TEST1="$var2 s s21_grep.h Makefile "
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          ((COUNTER_SUCCESS ++))
        else
          echo "./s21_grep $TEST1"
          ((COUNTER_FAIL++))
      fi
      rm s21_grep.txt grep.txt
    fi
  done
done
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
