#include "debugger.h"
#include "scanner.h"

void printTokens(List *tokens) {
  for (unsigned int i=0; i<tokens->size; ++i) {
    Token *tokenArr = tokens->head;
    if (i == 0 || tokenArr[i-1].line != tokenArr[i].line) {
      printf("%ld\t", tokenArr[i].line);
    } else {
      printf("|\t");
    }
    printf("%2d\t%.*s\n",tokenArr[i].type, tokenArr[i].end - tokenArr[i].start, tokenArr[i].start);
  }
}

void disassemble(ByteCode *byteCode) {
  
}