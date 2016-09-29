#!/bin/bash
outfile=$(date +%Y-%m-%d-%H-%M-%S)_decipher.run
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> "runs_normal/$outfile"
    (time ./decipher < "$file") &>> "runs_normal/$outfile"
done
