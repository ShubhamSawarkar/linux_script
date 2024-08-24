#include "vm.h"

#define NEXT_INSTRUCTION(vm) *vm.ip++

#define BINARY_OPERATION(arg1, op, arg2) arg1 op arg2

struct VM {
  opcode_size_t *ip;
  ByteCode *byteCode;
};

typedef struct VM VM;

InterpretResult interpret(ByteCode *byteCode) {
  VM vm = { byteCode->chunk.head,  byteCode };

  while (true) {
    OpCode instruction;
    switch (instruction = NEXT_INSTRUCTION(vm)) {
      case OP_ADD:
        break;
    }
  }
}