#!/bin/bash
g++ main.cpp geometry.cpp io.cpp -l ncurses -o main
./main
rm main
