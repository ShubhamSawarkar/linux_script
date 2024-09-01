#include "stack.h"
#include "list.h"

Stack stack(size_t item_len) {
  List ls = list(item_len);
  Stack st = { ls.head, ls };
  return st;
}

void push(Stack *stack, void *item) {
  size_t stack_len = (stack->top - stack->st.head) / stack->st.item_len;
  if (stack_len < stack->st.size) {
    update(&stack->st, stack_len, item);
  } else {
    add(&stack->st, item);
  }
  stack->top += stack->st.item_len;
}

void *pop(Stack *stack, void *dest) {
  if (stack->top == stack->st.head) return NULL;
  stack->top -= stack->st.item_len;
  memcpy(dest, stack->top, stack->st.item_len);
  return dest;
}

void destroy_stack(Stack *stack) {
  destroy_list(&stack->st);
}