CFLAGS = -mfpmath=sse \
         -fstack-protector-all \
         -W \
         -Wall \
         -Wextra \
         -Wunused \
         -Wcast-align \
         -Werror \
         -pedantic \
         -pedantic-errors \
         -Wfloat-equal \
         -Wpointer-arith \
         -Wformat-security \
         -Wmissing-format-attribute \
         -Wformat=1 \
         -Wwrite-strings \
         -Wcast-align \
         -Wno-long-long \
         -std=gnu99 \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -Wmissing-declarations \
         -Wold-style-definition \
         -Wdeclaration-after-statement \
         -Wbad-function-cast \
         -Wnested-externs \
		 -O3 \
		 -D_DEBUG -g \
		 -c

all: main.o array.o
	gcc main.o array.o -lssp && del *.o

main.o: main.c
	gcc $(CFLAGS) main.c

array.o: array.c
	gcc $(CFLAGS) array.c
