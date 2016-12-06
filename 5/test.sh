#!/bin/bash
# Tests my homework files 
# http://www.shellcheck.net/ is amazing

HW=prisoner
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW".run
dir="runs_normal"
if [[ ! -e $dir ]]; then
    mkdir $dir
fi

for file in tests/*.dat; do
    printf "\n\nTesting %s...\n" "$file" >> "$dir/$outfile"
    (time ./"$HW" < "$file") &>> "$dir/$outfile"
done
