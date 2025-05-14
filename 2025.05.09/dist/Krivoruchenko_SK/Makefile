FLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3

OBJ_COMMON = solve.o

NUMS = 1 2 3 4 5 6 7 8 9 10 11

OUTS = $(foreach n,$(NUMS),$(shell printf "a%02d.out\n" "$(n)"))

all: $(OUTS)

%.o: %.c
	gcc -c $(FLAGS) $<

a%.out: a%.o $(OBJ_COMMON)
	gcc $(FLAGS) $^ -o $@ -lm

clean:
	 rm -f *.o *.out
