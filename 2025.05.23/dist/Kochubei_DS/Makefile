OPTS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type -Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits -Wstrict-prototypes -Wmissing-field-initializers -Wno-pointer-sign -Wswitch-default -O3 -lm


all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

%.o: %.c
	gcc -c $(OPTS) $<

%.out: %.o
	gcc $(OPTS) $^ -o $@
	
solve.o: solve.c solve.h
add.o: add.c add.h

a01.o: a01.c solve.h add.h
a02.o: a02.c solve.h add.h
a03.o: a03.c solve.h add.h
a04.o: a04.c solve.h add.h
a05.o: a05.c solve.h add.h
a06.o: a06.c solve.h add.h
a07.o: a07.c solve.h add.h
a08.o: a08.c solve.h add.h
a09.o: a09.c solve.h add.h
a10.o: a10.c solve.h add.h

a01.out: a01.o solve.o add.o
a02.out: a02.o solve.o add.o
a03.out: a03.o solve.o add.o
a04.out: a04.o solve.o add.o
a05.out: a05.o solve.o add.o
a06.out: a06.o solve.o add.o
a07.out: a07.o solve.o add.o
a08.out: a08.o solve.o add.o
a09.out: a09.o solve.o add.o
a10.out: a10.o solve.o add.o


clean:
	rm *.o *.out
