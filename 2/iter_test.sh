#!/bin/bash
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> iter_decipher.output
    for i in $(seq 1 10); do
        ./decipher < "$file" >> iter_decipher.output
    done
done
