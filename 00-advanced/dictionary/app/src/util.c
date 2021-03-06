#include "util.h"
#include "hashtable.h"
#include "sllistc.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

char *stolower(char *src) {
  char *old = src;

  while (*src != '\0') {
    *src = tolower(*src);
    src++;
  }

  return old;
}

void print_callback(struct sl_node_t *node, struct sl_list_t *list, va_list argp) {
  struct spair_t *pair;
  FILE           *fs;

  fs   = va_arg(argp, FILE *);
  pair = sl_node_get_data(node);

  fprintf(fs, "%s -- %u\n", spair_get_key(pair), spair_get_value(pair));
}

void sl_list_print(struct sl_list_t *list, FILE *fs) {
  sl_list_iterate_over_nodes(list, print_callback, fs);
}