#!/usr/bin/bash

nasm -felf64 my_isalpha.s
gcc my_isalpha.o stub_test.o
./a.out