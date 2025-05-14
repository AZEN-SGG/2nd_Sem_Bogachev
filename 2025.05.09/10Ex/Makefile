WFLAGS = -fstack-protector-all -W -Wall -Wextra -Wunused \
-Wempty-body -Wlogical-op -Wold-style-declaration -Wmissing-parameter-type \
-Wignored-qualifiers -Winit-self -Wshadow -Wtype-limits \
-Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs \
-Wmissing-prototypes -Wmissing-declarations -Wold-style-definition \
-Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal \
-Wwrite-strings -Wno-long-long -std=gnu99 -Wstrict-prototypes \
-Wmissing-field-initializers -Wpointer-sign

LDFLAGS = -std=gnu99 -mfpmath=sse -O3
LDLIBS = -lm

ifeq ($(OS),Windows_NT)
	EXE = exe
	CLEAN = del
	LDLIBS += -lssp
else
	EXE = out
	CLEAN = rm -f
endif

TARGET = a10.$(EXE)
OBJ = main.o solve.o integral.o

%.o: %.c
	gcc $(WFLAGS) $(LDFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	gcc $^ -o $@ $(LDLIBS)

# Отладочная сборка (gdb)
gdb: LDFLAGS = -std=gnu99 -mfpmath=sse -g -O0
gdb: clean $(TARGET)

# Профилировочная сборка (gprof)
prof: LDFLAGS += -pg
prof: LDLIBS += -pg
prof: clean $(TARGET)

clean:
	$(CLEAN) *.o *.$(EXE)
