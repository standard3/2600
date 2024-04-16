#!/usr/bin/bash

input=$1

find "$input" -type f -not \( -path "*/travis/*" -o -path "*/doc/*" -o -path "*/rdoff/*" \) -regex '.*\.\(c\|h\|pl\|ph\|asm\|mac\|inc\|py\)' | sort