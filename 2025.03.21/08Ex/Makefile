CFLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused \
-Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type \
-Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits \
-Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs \
-Wmissing-prototypes -Wmissing-declarations -Wold-style-definition \
-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal \
-Wwrite-strings -Wno-long-long -std=gnu99 -Wstrict-prototypes \
-Wmissing-field-initializers -Wpointer-sign -O3

TARGET = a08.exe
OBJ = main.o array_io.o solve.o init_f.o

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(TARGET) -lssp

main.o: main.c
	gcc $(CFLAGS) -c main.c

solve.o: solve.c
	gcc $(CFLAGS) -c solve.c

array_io.o: array_io.c
	gcc $(CFLAGS) -c array_io.c

init_f.o: init_f.c
	gcc $(CFLAGS) -c init_f.c

clean:
	del *.o *.exe
