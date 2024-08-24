#include "stack.h"
#include "list.h"

Stack stack(size_t item_len) {
  Stack st = { list(item_len).head };
  return st;
}

void push(Stack *stack, void *item) {
  update(stack->top, item);
}

void *pop(Stack *stack) {
  update
}