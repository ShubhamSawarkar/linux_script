#include "scanner.h"
#include "debugger.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  /*List tokens = scan(argv[1]);
  printTokens(&tokens);
  destroy_list(&tokens);*/
  Value op1, op2, op3, op4;
  op1.number = 77;
  op2.number = 11;
  op3.number = 6;
  op4.number = 2;

  ByteCode code = byteCode();
  writeCodeChunk(&code, OP_LOAD, 1);
  writeConstant(&code, &op1, 1);
  writeCodeChunk(&code, OP_LOAD, 1);
  writeConstant(&code, &op2, 1);
  writeCodeChunk(&code, OP_DIVIDE, 1);
  writeCodeChunk(&code, OP_LOAD, 1);
  writeConstant(&code, &op4, 2);
  writeCodeChunk(&code, OP_MULTIPLY, 2);
  writeCodeChunk(&code, OP_LOAD, 2);
  writeConstant(&code, &op3, 2);
  writeCodeChunk(&code, OP_SUBSTRACT, 3);
  writeCodeChunk(&code, OP_RETURN, 4);

  interpret(&code);

  destroyByteCode(&code);
}