WFLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused \
-Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type \
-Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits \
-Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs \
-Wmissing-prototypes -Wmissing-declarations -Wold-style-definition \
-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal \
-Wwrite-strings -Wno-long-long -std=gnu99 -Wstrict-prototypes \
-Wmissing-field-initializers -Wpointer-sign

CFLAGS = -mfpmath=sse -std=gnu99 -O3

ifeq ($(OS),Windows_NT)
	EXE = exe
	CLEAN = del
	LFLAGS = -lssp -lm
else
	EXE = out
	CLEAN = rm -f
	LFLAGS = -lm
endif

TARGET = a.$(EXE)
OBJ = main.o solve.o array_io.o init_f.o matrix.o

%.o: %.c
	gcc $(CFLAGS) $(WFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	gcc $^ -o $@ $(LFLAGS)

# Отладочная сборка (gdb)
gdb: CFLAGS = -mfpmath=sse -std=gnu99 -g -O0
gdb: clean $(TARGET)

# Профилировочная сборка (gprof)
prof: CFLAGS = -mfpmath=sse -std=gnu99 -pg -O3 -fno-omit-frame-pointer
prof: clean $(TARGET)

clean:
	$(CLEAN) *.o *$(EXE)
