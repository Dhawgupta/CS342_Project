#!/usr/bin/env bash
gcc -c Layer0.c
gcc -c Layer1.c
echo Done compiling
gcc Layer1.o Layer0.o main.c -o main
