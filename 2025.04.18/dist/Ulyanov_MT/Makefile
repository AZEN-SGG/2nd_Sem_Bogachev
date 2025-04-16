FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -O3
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out
a01.out: a01.o array.o functions.o
	gcc a01.o array.o functions.o -lm -o a01.out
a02.out: a02.o array.o functions.o
	gcc a02.o array.o functions.o -lm -o a02.out
a03.out: a03.o array.o functions.o
	gcc a03.o array.o functions.o -lm -o a03.out
a04.out: a04.o array.o functions.o
	gcc a04.o array.o functions.o -lm -o a04.out
a05.out: a05.o array.o functions.o
	gcc a05.o array.o functions.o -lm -o a05.out
a06.out: a06.o array.o functions.o
	gcc a06.o array.o functions.o -lm -o a06.out
a07.out: a07.o array.o functions.o
	gcc a07.o array.o functions.o -lm -o a07.out
array.o:
	gcc -c $(FLAGS) -o array.o array.c
functions.o:
	gcc -c $(FLAGS) -o functions.o functions.c
a01.o:
	gcc -c $(FLAGS) -o a01.o task01.c
a02.o:
	gcc -c $(FLAGS) -o a02.o task02.c
a03.o:
	gcc -c $(FLAGS) -o a03.o task03.c
a04.o:
	gcc -c $(FLAGS) -o a04.o task04.c
a05.o:
	gcc -c $(FLAGS) -o a05.o task05.c
a06.o:
	gcc -c $(FLAGS) -o a06.o task06.c
a07.o:
	gcc -c $(FLAGS) -o a07.o task07.c
clean:
	rm -f *.o *.out
