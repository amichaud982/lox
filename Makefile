INC=-I./include
CC=gcc

lox: main.c chunk.c memory.c debug.c value.c vm.c
	$(CC) $(INC) -o lox vm.c value.c chunk.c memory.c main.c debug.c

clean:
	-rm lox

PHONY: clean lox
