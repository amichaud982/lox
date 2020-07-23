#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memory.h"
#include "value.h"
#include "vm.h"

Value nativeExit(int argCount, Value *args)
{
	printf("exiting...\n");
	collectGarbage();
	freeVM();
	exit(EXIT_SUCCESS);
	return NUMBER_VAL(0);
}

Value nativeClock(int argCount, Value *args)
{
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

Value nativePrint(int argCount, Value *args)
{
	for (int i = 0; i < argCount; ++i)
		printValue(*args++);
}

Value nativePrintln(int argCount, Value *args)
{
	for (int i = 0; i < argCount; ++i)
		printValue(*args++);
	printf("\n");
}
