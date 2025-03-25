FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -O3
all: a01.out a02.out a03.out
a01.out: a01.o array.o matrix.o
	gcc a01.o array.o matrix.o -lm -o a01.out
a02.out: a02.o array.o matrix.o
	gcc a02.o array.o matrix.o -lm -o a02.out
a03.out: a03.o array.o matrix.o
	gcc a03.o array.o matrix.o -lm -o a03.out
array.o:
	gcc -c $(FLAGS) -o array.o array.c
matrix.o:
	gcc -c $(FLAGS) -o matrix.o matrix.c
a01.o:
	gcc -c $(FLAGS) -o a01.o task01.c
a02.o:
	gcc -c $(FLAGS) -o a02.o task02.c
a03.o:
	gcc -c $(FLAGS) -o a03.o task03.c
clean:
	rm -f *.o *.out
