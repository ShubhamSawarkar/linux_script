#include "vm.h"
#include "type/stack.h"

#define NEXT_INSTRUCTION(vm) *vm.ip++

#define BINARY_OPERATION(arg1, op, arg2) TO_VAL(arg1 op arg2)

#define POP_VAL(st, dest) ((Value *) pop(&st, &dest))

struct VM {
  opcode_size_t *ip;
  ByteCode *byteCode;
};

typedef struct VM VM;

InterpretResult interpret(ByteCode *byteCode) {
  VM vm = { byteCode->chunk.head,  byteCode };
  Stack st = stack(sizeof(Value));

  while (true) {
    OpCode instruction;
    Value op1, op2;

    switch (instruction = NEXT_INSTRUCTION(vm)) {
      case OP_LOAD:
        push(&st, &TO_VAL(*((double *) byteCode->constants.head + *vm.ip)));
        NEXT_INSTRUCTION(vm);
        break;

      case OP_ADD:
        push(&st, &BINARY_OPERATION(POP_VAL(st, op1)->number, +, POP_VAL(st, op2)->number));
        break;

      case OP_SUBSTRACT:
        double subtrahend = POP_VAL(st, op2)->number;
        push(&st, &BINARY_OPERATION(POP_VAL(st, op1)->number, -, subtrahend));
        break;

      case OP_MULTIPLY:
        push(&st, &BINARY_OPERATION(POP_VAL(st, op1)->number, *, POP_VAL(st, op2)->number));
        break;

      case OP_DIVIDE:
        double divisor = POP_VAL(st, op2)->number;
        push(&st, &BINARY_OPERATION(POP_VAL(st, op1)->number, /, divisor));
        break;

      case OP_RETURN:
        printValue(pop(&st, &op1));
        return RESULT_SUCCESS;
        break;
    }
  }
}