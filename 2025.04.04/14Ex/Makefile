CFLAGS = -mfpmath=sse -fstack-protector-all -std=gnu99 -O3

WFLAGS = -W -Wall -Wextra -Wunused -Wempty-body -Wlogical-op \
	 -Wold-style-declaration -Wmissing-parameter-type \
	 -Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits \
	 -Wpointer-arith -Wformat-security -Wmissing-format-attribute \
	 -Wformat=1 -Wdeclaration-after-statement -Wbad-function-cast \
	 -Wnested-externs -Wmissing-prototypes -Wmissing-declarations \
	 -Wold-style-definition -Wcast-align -Werror -pedantic \
	 -pedantic-errors -Wfloat-equal -Wwrite-strings -Wno-long-long \
	 -Wstrict-prototypes -Wmissing-field-initializers -Wpointer-sign 

TARGET = a.out
OBJ = main.o solve.o array_io.o init_f.o matrix.o

%.o: %.c
	gcc $(CFLAGS) $(WFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	gcc $^ -o $@ -lm

gdb: CFLAGS = -mfpmath=sse -fstack-protector-all -std=gnu99 -g
gdb: clean $(TARGET)

clean:
	rm -f *.o *.out
