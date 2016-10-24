#!/bin/bash
# Simply does everything test does 10 times as much, so we can compare evolutions
# http://www.shellcheck.net/ is amazing

HW=points
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW"_iter-test.run
numTests=20
dir="runs_iter"
if [[ ! -e $dir ]]; then
    mkdir $dir
fi

for i in $(seq 2 $numTests); do
    printf "\n\nTesting %s...\n" "$i" >> "$dir/$outfile"
    for _ in $(seq 1 10); do
        (time ./"$HW" "$i") &>> "$dir/$outfile"
    done
done
