#include "stack.h"


TStack *createStack(size_t field_size, size_t content_size)
{
    TStack *stack = calloc(1, sizeof(TStack));
    
    if(!stack)
    {
        fprintf(stderr, "Failed to allocate stack!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    
    stack->_content = calloc(content_size, field_size);
    stack->_field_size = field_size;
    stack->_last = stack->_content;
    stack->_content_size = content_size;
    
    
    return stack;
}


void pushStack(void *item, TStack *stack)
{
    if(STACK_FULL(stack))
    {
        fprintf(stderr, "Stack overflow!\nItem was not added!\n");
    }
    else
    {
        memcpy(stack->_last, item, stack->_field_size);
        stack->_last += stack->_field_size;
    }
}

void popStack(TStack *stack)
{
    if(STACK_EMPTY(stack))
    {
        fprintf(stderr, "Stack underflow!\nItem was not removed!\n");
    }
    else
    {
        stack->_last -= stack->_field_size;
    }
}
