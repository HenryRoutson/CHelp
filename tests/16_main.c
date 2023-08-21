
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


/// CHELP

#include "../help/help.h"
CHELP_MAIN_MACRO

enum {
  UNTYPED,
  NODE_TYPE,
};

///




long node_count = 0;

typedef struct {
  void *data;
  int *next;
} node_t;

// init for stack and heap allocated types
void init_node(node_t *node) {
  node->data = NULL;
  node->next = NULL;
}

node_t *create_node() {
  node_t *node = malloc(sizeof(*node));
  init_node(node);
  set_alloc_type(node, NODE_TYPE, "node_t");
  return node;
}

void remove_node(node_t *node) {
  // complex logic for removing from linked list, ect...

  n_unfreed_of_type(NODE_TYPE, node_count);

  free(node);
  node_count--;
}


int main(void) {

	node_t *node1 = create_node();
  node_t *node2 = create_node();

  n_unfreed_of_type(NODE_TYPE, 2);

  print_all_allocs();

  remove_node(node1);
  remove_node(node2);

  print_all_allocs();
}