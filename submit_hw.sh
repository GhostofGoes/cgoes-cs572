#!/usr/bin/env bash

ass=$1

cd ./$ass
make
../curlsubmit goes8945 $ass $ass.tar
