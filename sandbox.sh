#!/usr/bin/env bash

arr=()
for var in $@
do
echo $var | awk '!/\.txt$/ {print $0".txt"} /\.txt$/ {print $0}'
done
