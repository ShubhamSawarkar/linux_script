#ifndef BYTECODE_H
#define BYTECODE_H

#include "type/list.h"
#include "value.h"

struct ByteCode {
  List chunk;
  List lines;
  List constants;
};

typedef struct ByteCode ByteCode;

enum OpCode {
  OP_LOAD,
  OP_ADD,
  OP_SUBSTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_RETURN
};

typedef enum OpCode OpCode;

typedef uint16_t opcode_size_t;

ByteCode byteCode();

void writeCodeChunk(ByteCode *byteCode, opcode_size_t chunk);

void writeConstant(ByteCode *byteCode, Value value);

void destroyByteCode(ByteCode *byteCode);

#endif