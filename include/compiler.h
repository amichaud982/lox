#ifndef clox_compiler_h
#define clox_compiler_h

#include "scanner.h"
#include "object.h"
#include "vm.h"

//#define UINT8_COUNT (UINT8_MAX + 1)

ObjFunction *compile(const char *source);
void markCompilerRoots(void);

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
    bool isCaptured;
} Local;

typedef struct
{
    uint8_t index;
    bool isLocal;
} Upvalue;

typedef enum
{
    TYPE_FUNCTION,
    TYPE_METHOD,
    TYPE_SCRIPT
} FunctionType;

typedef struct Compiler_t
{
    struct Compiler_t *enclosing;
    ObjFunction *function;
    FunctionType type;
    Local locals[UINT8_COUNT];
    int localCount;
    Upvalue upvalues[UINT8_COUNT];
    int scopeDepth;
} Compiler;

typedef struct ClassCompiler_t
{
    struct ClassCompiler_t *enclosing;
    Token name;
} ClassCompiler;

#endif
