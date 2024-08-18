#include "scanner.h"
#include "debugger.h"
int main(int argc, const char* argv[]) {
  List tokens = scan(argv[1]);
  printTokens(&tokens);
}