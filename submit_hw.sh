#!/usr/bin/env bash

ass=$1

cd ./$ass
make tar
../curlsubmit.sh goes8945 $ass $ass.tar
