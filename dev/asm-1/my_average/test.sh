#!/usr/bin/bash

nasm -felf64 my_average.s
gcc my_average.o stub_test.o
./a.out