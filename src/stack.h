#ifndef _STACK_H

#define _STACK_H

#include "structs.h"
#define STACK_EMPTY(stack) (stack->_last == stack->_content)
#define STACK_FULL(stack) (stack->_last == (stack->_content + stack->_content_size * stack->_field_size))

TStack *createStack(size_t field_size, size_t content_size);
void pushStack(void *item, TStack *stack);
void popStack(TStack *stack);



#endif
