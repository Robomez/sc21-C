#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
# TEST_FILE="$1"
TEST_FILE="test_files/test1.txt"
TEST_FILE2="test_files/test2.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  TEST1="$var $TEST_FILE" 
  echo "$TEST1"
  ./s21_cat $TEST1 > s21_cat.txt
  cat $TEST1 > cat.txt
  diff_result=$(diff s21_cat.txt cat.txt)
  if [ -z "$diff_result" ]; then
    COUNTER_SUCCESS=$((COUNTER_SUCCESS+=1))
  else 
    COUNTER_FAIL=$((COUNTER_FAIL+=1))
    echo "$TEST1" >> log.txt
  fi
  rm s21_cat.txt cat.txt
done


for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
    if [ $var != $var2 ]
    then
      TEST1="$var $var2 $TEST_FILE"
      echo "$TEST1"
      ./s21_cat $TEST1 > s21_cat.txt
      cat $TEST1 > cat.txt
      diff_result=$(diff s21_cat.txt cat.txt)
      if [ -z "$diff_result" ]; then
        COUNTER_SUCCESS=$((COUNTER_SUCCESS+=1))
      else 
        COUNTER_FAIL=$((COUNTER_FAIL+=1))
        echo "$TEST1" >> log.txt
      fi
      rm s21_cat.txt cat.txt
    fi
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
    for var3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
      then
        TEST1="$var $var2 $var3 $TEST_FILE"
        echo "$TEST1"
        ./s21_cat $TEST1 > s21_cat.txt
        cat $TEST1 > cat.txt
        diff_result=$(diff s21_cat.txt cat.txt)
        if [ -z "$diff_result" ]; then
          COUNTER_SUCCESS=$((COUNTER_SUCCESS+=1))
        else 
          COUNTER_FAIL=$((COUNTER_FAIL+=1))
          echo "$TEST1" >> log.txt
        fi
        rm s21_cat.txt cat.txt
      fi
    done
  done
done

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for var2 in b e n s t v #-E -T --number-nonblank --number --squeeze-blank
  do
    for var3 in b e n s t v #-E -T --number-nonblank --number --squeeze-blank
    do
      for var4 in "$TEST_FILE" "$TEST_FILE $TEST_FILE2" #-E -T --number-nonblank --number --squeeze-blank
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var$var2$var3  $var4"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          diff_result=$(diff s21_cat.txt cat.txt)
          if [ -z "$diff_result" ]; then
            COUNTER_SUCCESS=$((COUNTER_SUCCESS+=1))
          else 
            COUNTER_FAIL=$((COUNTER_FAIL+=1))
            echo "$TEST1" >> log.txt
          fi
          rm s21_cat.txt cat.txt
        fi
      done
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -eq 0 ]
then
  rm log.txt
fi

exit "$COUNTER_FAIL"