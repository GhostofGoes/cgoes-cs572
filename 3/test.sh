#!/bin/bash
# Tests my homework files 
# http://www.shellcheck.net/ is amazing

HW=points
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW".run
numTests=20
dir="runs_normal"
if [[ ! -e $dir ]]; then
    mkdir $dir
fi

for i in $(seq 2 $numTests); do
    printf "\n\nTesting %s...\n" "$i" >> "$dir/$outfile"
    (time ./"$HW" "$i") &>> "$dir/$outfile"
done
