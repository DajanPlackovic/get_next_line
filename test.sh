#!/usr/bin/env bash

echo "NORMINETTE ERRORS"
norminette get_next_line.c | awk '!/OK!$/'
norminette get_next_line_utils.c | awk '!/OK!$/'
norminette get_next_line.h | awk '!/OK!$/'
printf "%s " "Press enter to continue"
read ans
cc *.c -g -L. -lft
# if there are no arguments
if [ $# -eq 0 ]; then
# run tests with all files
./a.out $(ls *.txt)
else
arr=()
for var in $@
do
arr+=($(echo $var | awk '!/\.txt$/ {print $0".txt"} /\.txt$/ {print $0}'))
done
./a.out "${arr[@]}"
fi
