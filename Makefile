INC=-I./include
CC=gcc

lox: main.c chunk.c compiler.c memory.c debug.c value.c vm.c scanner.c
	$(CC) $(INC) -o lox scanner.c compiler.c vm.c value.c chunk.c memory.c main.c debug.c

clean:
	-rm lox

PHONY: clean lox
