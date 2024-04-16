#!/usr/bin/bash

input=$(echo $1 | cut -d ' ' -f2-)

if [[ "$input" =~ ^[0-9]+$ ]]; then
    echo "INT $input"

elif [[ "$input" =~ ^([a-z]+)$ ]]; then
    echo "LOWER $input"

elif [[ "$input" =~ ^([A-Z]|_).+$ ]]; then
    echo "IDENT $input"

elif [[ "$input" =~ ^(\"|\').*(\"|\')$ ]]; then
    str="${input:1:${#input}-2}"
    echo "STR ${str//\\}"

else
    echo "Unknown"
fi
