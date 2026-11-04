#include "stack.h"

#include <stdlib.h>

// err codes:
// STACK_INIT_FAILED
// STACK_OVERFLOW
// STACK_EMPTY

error_status u32_stack_init(u32_stack* s, uint32_t size)
{
    s->size = size; 
    s->ins = 0;
    s->array = malloc(size *  sizeof(uint32_t));
    return SUCCESS;
}

error_status u32_stack_push(u32_stack* s, uint32_t item);
{
    if (s->ins == s->size) return STACK_OVERFLOW;
    s->array[s->ins++] = item;
    return SUCCESS;
}

error_status u32_stack_pop(u32_stack* s);
{
    if (s->ins == 0) return STACK_EMPTY;
    s->[s->ins--] = 0;
    return SUCCESS;
}

uint32_t u32_stack_top(u32_stack* s);
{
    if (s->ins == 0) return 0;
    return s->s[ins];
}

