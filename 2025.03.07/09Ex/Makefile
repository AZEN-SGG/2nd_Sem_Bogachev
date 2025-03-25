FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

a09.out: main.o array_io.o solve.o init_f.o
	gcc main.o solve.o array_io.o init_f.o -o a09.out 

main.o: main.c
	gcc $(CFLAGS) -c main.c

solve.o: solve.c
	gcc $(FLAGS) -c solve.c

array_io.o: array_io.c
	gcc $(CFLAGS) -c array_io.c

init_f.o: init_f.c
	gcc $(CFLAGS) -c init_f.c

clean:
	rm *.o *.out
