#ifndef clox_compiler_h
#define clox_compiler_h

#include "scanner.h"
#include "object.h"
#include "vm.h"

//#define UINT8_COUNT (UINT8_MAX + 1)

ObjFunction *compile(const char *source);

typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,    // =
    PREC_OR,            // or
    PREC_AND,           // and
    PREC_EQUALITY,      // == !=
    PREC_COMPARISON,    // < > <= >=
    PREC_TERM,          // + -
    PREC_FACTOR,        // * /
    PREC_UNARY,         // ! -
    PREC_CALL,          // . ()
    PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)(bool canAssign);

typedef struct
{
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

typedef struct
{
    Token name;
    int depth;
} Local;

typedef enum
{
    TYPE_FUNCTION,
    TYPE_SCRIPT
} FunctionType;

typedef struct
{
    ObjFunction *function;
    FunctionType type;
    Local locals[UINT8_COUNT];
    int localCount;
    int scopeDepth;
} Compiler;

#endif
