#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct Stack {
  void *top;
};

typedef struct Stack Stack;

Stack stack(size_t item_len);

void push(Stack *stack, void *item);

void *pop(Stack *stack);

void destroy_stack(Stack *stack);

#endif