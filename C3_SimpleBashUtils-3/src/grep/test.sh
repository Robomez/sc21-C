#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
EXP_TEXT="my"
EXP_FILE="test_files/test_pattern"
TEST_FILE1="test_files/dust.txt"
TEST_FILE2="test_files/champ.txt"
echo "" > log.txt

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "4 PARAMETERS"
echo "2 FILES"
echo "======================="
printf "\n"

for var1 in "-e dust -e" -i -v -c -l -n -h -s "-f eregs.txt -e" -o
do
  for var4 in -i -v -c -l -n -h -s -o
  do
    for var5 in i v c l n h s o
    do
      for var3 in "$TEST_FILE1" "$TEST_FILE1 $TEST_FILE2"
      do
        TEST1="$var1 $EXP_TEXT $var3 $var4$var5"
        echo "$TEST1"
        ./s21_grep $TEST1 > s21_grep.txt
        grep $TEST1 > grep.txt
        diff_result=$(diff s21_grep.txt grep.txt)
        if [ -z "$diff_result" ]; then
          COUNTER_SUCCESS=$((COUNTER_SUCCESS+=1))
        else 
          COUNTER_FAIL=$((COUNTER_FAIL+=1))
          echo "$TEST1" >> log.txt
        fi
        rm s21_grep.txt grep.txt
      done
    done
  done
done

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "grep"
    )

flags=(
    "v"
    "c"
    "l"
    "n"
    "h"
    "o"
)

tests=(
    "s test_files/test_0_grep.txt FLAGS"
    "for s21_grep.c s21_grep.h Makefile FLAGS"
    "for s21_grep.c FLAGS"
    "-e for -e ^int s21_grep.c s21_grep.h Makefile FLAGS"
    "-e for -e ^int s21_grep.c FLAGS"
    "-e regex -e ^print s21_grep.c FLAGS -f test_files/test_ptrn_grep.txt"
    "-e while -e void s21_grep.c Makefile FLAGS -f test_files/test_ptrn_grep.txt"
    "-e intel -e int FLAGS test_files/test_7_grep.txt"
    "-e int -e intel FLAGS test_files/test_7_grep.txt"
)

manual=(
    "-n for test_files/test_1_grep.txt test_files/test_2_grep.txt"
    "-n for test_files/test_1_grep.txt"
    "-n -e ^\} test_files/test_1_grep.txt"
        # "-c -e /\ test_files/test_1_grep.txt"
    "-ce ^int test_files/test_1_grep.txt test_files/test_2_grep.txt"
    "-e ^int test_files/test_1_grep.txt"
    "-nivh = test_files/test_1_grep.txt test_files/test_2_grep.txt"
    "-e"
    "-ie INT test_files/test_5_grep.txt"
    "-echar test_files/test_1_grep.txt test_files/test_2_grep.txt"
    "-ne = -e out test_files/test_5_grep.txt"
    "-iv int test_files/test_5_grep.txt"
    "-in int test_files/test_5_grep.txt"
    "-c -l aboba test_files/test_1_grep.txt test_files/test_5_grep.txt"
    "-v test_files/test_1_grep.txt -e ank"
    "-noe ) test_files/test_5_grep.txt"
    "-l for test_files/test_1_grep.txt test_files/test_2_grep.txt"
    "-o -e int test_files/test_4_grep.txt"
    "-e = -e out test_files/test_5_grep.txt"
    "-noe ing -e as -e the -e not -e is test_files/test_6_grep.txt"
    "-e ing -e as -e the -e not -e is test_files/test_6_grep.txt"
        # "-c -e . test_files/test_1_grep.txt -e '.'"
    "-l for no_file.txt test_files/test_2_grep.txt"
    "-e int -si no_file.txt s21_grep.c no_file2.txt s21_grep.h"
    "-si s21_grep.c -f no_pattern.txt"
    "-f test_files/test_3_grep.txt test_files/test_5_grep.txt"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${s21_command[@]}" $param > "${s21_command[@]}".log
    "${sys_command[@]}" $param > "${sys_command[@]}".log
    DIFF="$(diff -s "${s21_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${s21_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "COUNTER_SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "COUNTER_FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}

printf "\n"
echo "#######################"
echo "MANUAL TESTS"
echo "#######################"
printf "\n"

for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -eq 0 ]
then
  rm log.txt
fi

exit "$COUNTER_FAIL"