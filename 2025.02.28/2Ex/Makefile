FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

a02.exe: main.o array.o solve.o sort.o
	gcc main.o solve.o array.o sort.o -o a02.exe -lssp

main.o: main.c
	gcc $(CFLAGS) -c main.c

solve.o: solve.c
	gcc $(FLAGS) -c solve.c

array.o: array.c
	gcc $(CFLAGS) -c array.c

sort.o: sort.c
	gcc $(CFLAGS) -c sort.c

clean:
	del *.o *.exe
