FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

%.out: %.o array.o comparison.o
	 gcc $(FLAGS) $^ -o $@ -lm
%.o: %.c
	 gcc -c $(FLAGS) $<

all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

array.o: array.c array.h
comparison.o: comparison.c comparison.h

clean:
	 rm *.o *.out
