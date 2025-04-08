#!/bin/bash

for k in 1 2 ; do echo "k=$k a.txt ---------------"   ; ./a.out 4 3 $k /users/data/matr/a.txt   ; done
for k in 1 2 ; do echo "k=$k a20.txt ---------------" ; ./a.out 4 3 $k /users/data/matr/a20.txt ; done
for k in 1 2 ; do echo "k=$k b.txt ---------------"   ; ./a.out 4 3 $k /users/data/matr/b.txt   ; done
for k in 1 2 ; do echo "k=$k c.txt ---------------"   ; ./a.out 6 3 $k /users/data/matr/c.txt   ; done
for k in 1 2 ; do echo "k=$k d.txt ---------------"   ; ./a.out 6 3 $k /users/data/matr/d.txt   ; done
for k in 1 2 ; do echo "k=$k e.txt ---------------"   ; ./a.out 6 3 $k /users/data/matr/e.txt   ; done
for k in 1 2 ; do echo "k=$k f.txt ---------------"   ; ./a.out 6 3 $k /users/data/matr/f.txt   ; done
