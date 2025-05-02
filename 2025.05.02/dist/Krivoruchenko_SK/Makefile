FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

%.out: %.o solve.o init_f.o
	 gcc $(FLAGS) $^ -o $@ -lm
%.o: %.c
	 gcc -c $(FLAGS) $<

all: a01.out a02.out a03.out a04.out a07.out a08.out a09.out

solve.o: solve.c solve.h
init_f.o: init_f.c init_f.h

clean:
	 rm -f *.o *.out
