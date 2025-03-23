FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

a07.exe: main.o solve.o
	gcc main.o solve.o -o a07.exe -lssp

main.o: main.c
	gcc $(CFLAGS) -c main.c

solve.o: solve.c
	gcc $(FLAGS) -c solve.c

clean:
	del *.o *.exe