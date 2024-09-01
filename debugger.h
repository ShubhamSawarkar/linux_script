#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "type/list.h"
#include "bytecode.h"

void printTokens(List *token);

void disassemble(ByteCode *byteCode);

#endif