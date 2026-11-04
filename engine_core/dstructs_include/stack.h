#ifndef _STACK_
#define _STACK_

#include <stdint.h>
#include "error.h"

// Unsigned 32 bit int stack.
//======================================================== 

// Definition
typedef struct
{
    uint32_t size;
    uint32_t ins;
    uint32_t* array;
} u32_stack; 

// Initializes an ui32_stack 
error_status u32_stack_init(u32_stack* s, uint32_t size);

//
// Initializes an ui32_stack 
//error_status u32_stack_resize(u32_stack* s, uint32_t size);

// Pushes uint32_t to top of stack
error_status u32_stack_push(u32_stack* s, uint32_t item);

// Pops uint32_t from top of stack
error_status u32_stack_pop(u32_stack* s);

// Returns the top item of the stack, 0 if none
uint32_t u32_stack_top(u32_stack* s);

#endif
