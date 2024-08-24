#ifndef VM_H
#define VM_H

#include "bytecode.h"

enum InterpretResult {
  RESULT_SUCCESS,
  RESULT_COMPILATION_ERROR,
  RESULT_RUNTIME_ERROR
};

typedef enum InterpretResult InterpretResult;

InterpretResult interpret(ByteCode *byteCode);

#endif