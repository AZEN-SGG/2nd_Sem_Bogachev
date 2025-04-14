#!/bin/bash
# 300 runs
for ((n=1; n<=300;n++)) ; do echo "--------- n=$n ----------" ; ./a.out $n ; done
