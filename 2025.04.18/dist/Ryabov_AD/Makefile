all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out

CFLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors \
	 -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long \
	 -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
	 -Wnested-externs -Wmaybe-uninitialized -lm

a%.out: task%.o solve.o massiv_io.o
	gcc $(CFLAGS) $^ -o $@ -lm

task%.o: task%.c io_status.h massiv_io.h solve.h
	gcc -c $(CFLAGS) $<

massiv_io.o: massiv_io.c massiv_io.h
	gcc -c $(CFLAGS) massiv_io.c 

solve.o: solve.c solve.h
	gcc -c $(CFLAGS) solve.c
	
clean:
	rm *.o
