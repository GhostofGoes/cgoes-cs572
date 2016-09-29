#!/bin/bash
outfile=$(date +%Y-%m-%d-%H-%M-%S)_decipher_iter-test.run
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> "$outfile"
    for i in $(seq 1 10); do
        ./decipher < "$file" >> "$outfile"
    done
done
