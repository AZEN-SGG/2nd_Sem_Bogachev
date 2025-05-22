FLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -O3
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out
a01.out: a01.o list.o
	gcc a01.o list.o -o a01.out
a02.out: a02.o list.o
	gcc a02.o list.o -o a02.out
a03.out: a03.o list.o
	gcc a03.o list.o -o a03.out
a04.out: a04.o list.o
	gcc a04.o list.o -o a04.out
a05.out: a05.o list.o
	gcc a05.o list.o -o a05.out
a06.out: a06.o list.o
	gcc a06.o list.o -o a06.out
a07.out: a07.o list.o
	gcc a07.o list.o -o a07.out
a08.out: a08.o list.o
	gcc a08.o list.o -o a08.out
list.o:
	gcc -c $(FLAGS) -o list.o list.c
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
a08.o:
	gcc -c $(FLAGS) -o a08.o task08.c
clean:
	rm -f *.o *.out
