#!/usr/bin/env bash

ass="$1"
# test="$2"
path="../test_data/$ass/";

cd ./$ass
make test
./$ass $path | tee $1_results_$(date +%j-%k-%M).output
