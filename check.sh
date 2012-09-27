#!/bin/bash
rm main.exe*
g++ -Wall -o main hdu4419_Colourful\ Rectangle\(seg-tree2\).cpp
./main < h.in > h.out
diff -q h.out h.ans
#./main < h.in
#cat h.ans
