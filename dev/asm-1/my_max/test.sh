#!/usr/bin/bash

nasm -felf64 my_max.s
gcc my_max.o stub_test.o
./a.out