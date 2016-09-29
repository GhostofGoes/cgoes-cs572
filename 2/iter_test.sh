#!/bin/bash
outfile=$(date +%Y-%m-%d-%H-%M-%S)_decipher_iter-test.run
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> "runs_iter/$outfile"
    for i in $(seq 1 10); do
        (time ./decipher < "$file") &>> "runs_iter/$outfile"
    done
done
