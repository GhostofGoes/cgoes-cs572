#!/bin/bash
# Profiles  my homework files 
# http://www.shellcheck.net/ is amazing

HW=func
outfile=$(date +%Y-%m-%d-%H-%M-%S)_"$HW".profile
dir="profiling"
if [[ ! -e $dir ]]; then
    mkdir $dir
fi

if [[ ! $1 ]]; then
    echo "Must specify name of test file"
    exit
fi

make profile

(printf "Running with test file %s.dat\n" "$1") >> "$dir/$outfile"
(time ./"$HW" < tests/"$1".dat) &>> "$dir/$outfile"
(printf "\n\n") &>> "$dir/$outfile"
(gprof "$HW") &>> "$dir/$outfile"
rm gmon.out
