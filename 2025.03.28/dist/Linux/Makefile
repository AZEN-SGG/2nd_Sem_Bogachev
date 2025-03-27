FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -fopenmp -O3

%.out: %.o solve.o array_io.o init_f.o matrix.o
	 gcc $(FLAGS) $^ -o $@ -lm -fopenmp
%.o: %.c
	 gcc -c $(FLAGS) $<

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out

solve.o: solve.c solve.h
array_io.o: array_io.c array_io.h
init_f.o: init_f.c init_f.h
matrix.o: matrix.c matrix.h

clean:
	 rm -f *.o *.out
