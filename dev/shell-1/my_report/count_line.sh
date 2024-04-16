#!/usr/bin/bash

shopt -s extglob

input=$1
filename=$(basename -- "$input")
ext="${input##*.}"

case $ext in 
    @(pl|ph|sh|py))
        grep -vE '^\s*#.*$|^$' $input | wc -l
    ;;
    @(asm|mac|inc))
        grep -vE '^\s*;.*$|^$' $input | wc -l
    ;;
    @(c|h))
        cpp -fpreprocessed -P $input | wc -l
    ;;
esac
