#!/bin/bash

for k in 1 2 ; do echo "k=$k a.txt ---------------"   ; mpirun -np $k ./a.out 4 3 /users/data/matr/a.txt   ; done
for k in 1 2 ; do echo "k=$k a20.txt ---------------" ; mpirun -np $k ./a.out 4 3 /users/data/matr/a20.txt ; done
for k in 1 2 ; do echo "k=$k b.txt ---------------"   ; mpirun -np $k ./a.out 4 3 /users/data/matr/b.txt   ; done
for k in 1 2 ; do echo "k=$k c.txt ---------------"   ; mpirun -np $k ./a.out 6 3 /users/data/matr/c.txt   ; done
for k in 1 2 ; do echo "k=$k d.txt ---------------"   ; mpirun -np $k ./a.out 6 3 /users/data/matr/d.txt   ; done
for k in 1 2 ; do echo "k=$k e.txt ---------------"   ; mpirun -np $k ./a.out 6 3 /users/data/matr/e.txt   ; done
for k in 1 2 ; do echo "k=$k f.txt ---------------"   ; mpirun -np $k ./a.out 6 3 /users/data/matr/f.txt   ; done
