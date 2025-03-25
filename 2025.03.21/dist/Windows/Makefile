FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

%.exe: %.o solve.o array_io.o init_f.o
	 gcc $(FLAGS) $^ -o $@ -lm
%.o: %.c
	 gcc -c $(FLAGS) $<

all: a01.exe a02.exe a03.exe a04.exe a05.exe a06.exe a07.exe a08.exe a09.exe a10.exe

solve.o: solve.c solve.h
array_io.o: array_io.c array_io.h
init_f.o: init_f.c init_f.h

clean:
	 del *.o *.exe
