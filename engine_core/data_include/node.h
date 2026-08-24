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

#endif
