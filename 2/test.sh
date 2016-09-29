#!/bin/bash
outfile=$(date +%Y-%m-%d-%H-%M-%S)_decipher.run
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> "$outfile"
    ./decipher < "$file" >> "$outfile"
done
