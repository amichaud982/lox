#ifndef clox_parser_h
#define clox_parser_h

#include "scanner.h"

typedef struct
{
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

#endif
