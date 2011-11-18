
CC = cc
CFLAGS = -g -pedantic -Wall -Os ${INCS} ${CPPFLAGS}

SRC = libtcp-portmon.c main.c
OBJ = ${SRC:.c=.o}

all: main

.c.o:
	${CC} -c ${CFLAGS} $<

main: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f *.o main

.PHONY: all clean main
