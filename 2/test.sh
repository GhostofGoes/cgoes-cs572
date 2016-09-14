#!/bin/bash
for file in codes/*.code; do
    echo "\n\nTesting $file...\n" >> test_decipher.output
    ./decipher < $file >> test_decipher.output
done
