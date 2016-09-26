#!/bin/bash

for file in codes/*.code; do
    printf "\n\nTesting %s...\n" "$file" >> decipher.output
    ./decipher < "$file" >> decipher.output
done
