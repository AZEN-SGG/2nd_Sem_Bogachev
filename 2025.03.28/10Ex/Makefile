CFLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused \
-Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type \
-Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits \
-Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs \
-Wmissing-prototypes -Wmissing-declarations -Wold-style-definition \
-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal \
-Wwrite-strings -Wno-long-long -std=gnu99 -Wstrict-prototypes \
-Wmissing-field-initializers -Wpointer-sign -fopenmp -O3

TARGET = a10.out
OBJ = main.o solve.o array_io.o init_f.o matrix.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	gcc $^ -o $@ -lm -fopenmp 

clean:
	rm *.o *.out
