#ifndef LIST_H
#define LIST_H

#include "../common.h"

#define INTITAL_LIST_SIZE 10

struct List {
  void *head;
  size_t item_len;
  size_t size;
  size_t capacity;
};

typedef struct List List;

List list(size_t item_len);

void add(List *list, void *item);

void update(List *list, size_t index, void *item);

void destroy_list(List *list);

#endif
