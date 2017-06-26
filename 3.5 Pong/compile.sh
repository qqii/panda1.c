#!/bin/bash

outputfile="pong.o"
flags="-O3 -std=c99 -pedantic -Wall -Werror -lncurses"
files=$(find *.c)

if [ -e "$outputfile" ]; then
  rm "pong.o"
fi


gcc $flags $files -o $outputfile
./$outputfile
