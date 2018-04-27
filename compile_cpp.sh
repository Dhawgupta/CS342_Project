#!/usr/bin/env bash
g++ -c Layer0.cpp
g++ -c Layer1.cpp
echo Done Compiling Linking Left
g++ Layer1.o Layer0.o main.cpp -o main
echo Linking Complete