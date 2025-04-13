FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -O3
all: a.out
a.out: a.o array.o matrix.o
	gcc a.o array.o matrix.o -lm -o a.out
array.o:
	gcc -c $(FLAGS) -o array.o array.c
matrix.o:
	gcc -c $(FLAGS) -o matrix.o matrix.c
a.o:
	gcc -c $(FLAGS) -o a.o task20.c
clean:
	rm -f *.o *.out
