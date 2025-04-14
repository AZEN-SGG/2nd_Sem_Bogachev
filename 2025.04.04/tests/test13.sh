#!/bin/bash
# 145 runs
for ((n=2; n<=30;n++)) ; do for ((m=3;m<=$n;m+=3)) ; do echo "n=$n m=$m" ; ./a.out $n $m ; done ; done
