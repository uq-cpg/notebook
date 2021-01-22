#!/bin/bash

for((i = 1; ; ++i)); do
    echo $i
    python3 gen.py $i > inp.txt
    ./main < inp.txt > out.txt
    ./slow < inp.txt > ans.txt
    diff -w out.txt ans.txt || break
done