INC=-I./include
CC=gcc
CFLAGS=pg

lox: main.c chunk.c compiler.c memory.c debug.c value.c vm.c scanner.c object.c table.c
	$(CC) $(INC) -$(CFLAGS) -o lox object.c scanner.c compiler.c vm.c value.c chunk.c memory.c main.c debug.c table.c

clean:
	-rm lox

PHONY: clean lox
