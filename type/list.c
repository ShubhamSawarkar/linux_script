#include "../type/list.h"

List list(size_t item_len) {
  List l;
  l.head = malloc(item_len * INTITAL_LIST_SIZE);
  l.item_len = item_len;
  l.size = 0;
  l.capacity = INTITAL_LIST_SIZE;
  return l;
}

static void expandList(List *list) {
  void *new_head = malloc(list->item_len * list->capacity * 2);
  memcpy(new_head, list->head, list->size * list->item_len);
  free(list->head);
  list->head = new_head;
  list->capacity *= 2;
}

void add(List *list, void *item) {
  if (list->size + 1 > list->capacity) {
    expandList(list);
  }
  memcpy(list->head + list->item_len * list->size, item, list->item_len);
  ++list->size;
}

void destroy_list(List *list) {
  if (list->head != NULL) {
    free(list->head);
  }
  list->head = NULL;
  list->size = 0;
  list->capacity = 0;
}