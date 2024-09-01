#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "list.h"

struct Stack {
  void *top;
  List st;
};

typedef struct Stack Stack;

Stack stack(size_t item_len);

void push(Stack *stack, void *item);

void *pop(Stack *stack, void *dest);

void destroy_stack(Stack *stack);

#endif