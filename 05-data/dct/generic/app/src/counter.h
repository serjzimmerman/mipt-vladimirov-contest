#ifndef COUNTER_H
#define COUNTER_H

#include "hashtable.h"
#include <stddef.h>

struct counter_t {
  struct hash_table_t *table;
};

struct counter_t *counter_init();
void counter_item_add(struct counter_t *counter, char *key);
unsigned counter_item_get_count(struct counter_t *counter, char *key);
void counter_free(struct counter_t *counter);

#endif