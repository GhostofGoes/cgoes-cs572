#!/bin/bash

HW=hw3
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW"_iter-test.run

for file in tests/*.test; do
    printf "\n\nTesting %s...\n" "$file" >> "runs_iter/$outfile"
    for _ in $(seq 1 10); do
        (time ./"$HW" < "$file") &>> "runs_iter/$outfile"
    done
done
