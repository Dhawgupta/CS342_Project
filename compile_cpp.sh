#!/usr/bin/env bash
g++ -c Layer0.cpp
g++ -c Layer1.cpp
g++ -c Layer2.cpp
echo Done Compiling Linking Left
g++ Layer1.o Layer0.o Layer2.o main_prog.cpp -o main_prog
echo Linking Complete