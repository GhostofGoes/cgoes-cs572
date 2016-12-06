#!/bin/bash
# Simply does everything test does 10 times as much, so we can compare evolutions
# http://www.shellcheck.net/ is amazing

HW=prisoner
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW"_iter-test.run
dir="runs_iter"
if [[ ! -e $dir ]]; then
    mkdir $dir
fi

for file in tests/*.dat; do
    printf "\n\nTesting %s...\n" "$file" >> "$dir/$outfile"
    for _ in $(seq 1 10); do
        (time ./"$HW" < "$file") &>> "$dir/$outfile"
    done
done
