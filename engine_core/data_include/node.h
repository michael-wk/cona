#ifndef _NODE_
#define _NODE_

#include <stdint.h>

typedef struct node_struct
{
    struct node_struct** children;
    struct node_struct* parent;
    uint8_t root;
} node;

void node_init(node* n);

// Adds a child node to passed node with name N.
node* node_add_node(node* n, char* name);

#endif
