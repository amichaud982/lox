#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

Value nativeType(int argCount, Value *args)
{
    Value value = args[0];
    if (argCount > 1) {
        printf("type() takes only one argument.\n");
        return NIL_VAL;
    }
    else if (argCount == 0) {
        printf("type() takes one argument.\n");
        return NIL_VAL;
    }
    
    char *msg;
    if (IS_OBJ(value)) {
        switch (OBJ_TYPE(value)) {
            case OBJ_BOUND_METHOD:
                msg = "<ObjBoundMethod>";
                break;
            case OBJ_CLASS:
                msg = "<ObjClass>";
                break;
            case OBJ_CLOSURE:
                msg = "<ObjClosure>";
                break;
            case OBJ_FUNCTION:
                msg = "<ObjFunction>";
                break;
            case OBJ_INSTANCE:
                msg = "<ObjInstance>";
                break;
            case OBJ_NATIVE:
                msg = "<ObjNative>";
                break;
            case OBJ_UPVALUE:
                msg = "<ObjUpvalue>";
                break;
            case OBJ_STRING:
                msg = "<ObjString>";
                break;
        }
    }
    else if (IS_BOOL(value))
        msg = "<bool>";
    else if (IS_NIL(value))
        msg = "<nil>";
    else if (IS_NUMBER(value))
        msg = "<number>";
    else
        msg = "unknown type";

    return OBJ_VAL(copyString(msg, strlen(msg)));
}

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

Value nativeInput(int argCount, Value *args)
{
    char buffer[1024];
    int length;

    for (int i = 0; i < argCount; ++i)
        printf("%s", AS_CSTRING(args[i]));

    fgets(buffer, sizeof(buffer), stdin);

    length = strlen(buffer);
    length[buffer-1] = '\0';
    ObjString *result = copyString(buffer, length);
    return OBJ_VAL(result);
}
