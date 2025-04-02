OPTS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -Wmaybe-uninitialized -Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type -Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits -Wstrict-prototypes -Wmissing-field-initializers -Wno-pointer-sign -Wswitch-default -fopenmp -O3


all: a.exe

%.o: %.c
	gcc -c $(OPTS) $<

%.exe: %.o
	gcc $(OPTS) $^ -o $@
	
solve.o: solve.c solve.h
add.o: add.c add.h

a.o: a.c solve.h add.h

a.exe: a.o solve.o add.o
