#include "bytecode.h"

ByteCode byteCode() {
  ByteCode byteCode;
  byteCode.chunk = list(sizeof(opcode_size_t));
  byteCode.lines = list(sizeof(opcode_size_t));
  byteCode.constants = list(sizeof(opcode_size_t));
  return byteCode;
}

void writeCodeChunk(ByteCode *byteCode, opcode_size_t chunk, size_t line) {
  add(&byteCode->chunk, &chunk);
  add(&byteCode->lines, &line);
}

void writeConstant(ByteCode *byteCode, Value *value, size_t line) {
  add(&byteCode->constants, &value->number);
  add(&byteCode->chunk, byteCode->constants.size - 1);
  add(&byteCode->lines, &line);
}

void destroyByteCode(ByteCode *byteCode) {
  destroy_list(&byteCode->chunk);
  destroy_list(&byteCode->lines);
  destroy_list(&byteCode->constants);
}