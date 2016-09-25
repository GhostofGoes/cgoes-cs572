#!/bin/bash
for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> test_decipher.output
    ./decipher < "$file" >> test_decipher.output
done
