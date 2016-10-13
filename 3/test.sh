#!/bin/bash

HW=hw3
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW".run

for file in tests/*.test; do
    printf "\n\nTesting %s...\n" "$file" >> "runs_normal/$outfile"
    (time ./"$HW" < "$file") &>> "runs_normal/$outfile"
done
