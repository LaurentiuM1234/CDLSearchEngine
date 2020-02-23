#include "queue.h"



TQueue *createQueue(size_t field_size, size_t content_size)
{
    TQueue *queue = calloc(1, sizeof(TQueue));
    
    queue->_content_size = content_size;
    queue->_field_size = field_size;
    queue->_content = calloc(content_size, field_size);
    queue->_front = queue->_content;
    queue->_rear = queue->_content;
    queue->_is_empty_flag = 1;
    
    return queue;
}

void pushQueue(void *item, TQueue *queue)
{
    if(QUEUE_FULL(queue))
    {
        fprintf(stderr, "Queue overflow!\nItem was not added!\n");
    }
    else
    {
        memcpy(queue->_front, item, queue->_field_size);
        queue->_front += queue->_field_size;
        queue->_is_empty_flag = 0;
    }
}

void popQueue(TQueue *queue)
{
    if(QUEUE_EMPTY(queue))
    {
        fprintf(stderr, "Queue underflow!\nItem was not removed!\n");
    }
    else
    {
        queue->_rear += queue->_field_size;
        
        if(memcmp(queue->_front, queue->_rear, queue->_field_size) == 0)
        {
            queue->_front = queue->_content;
            queue->_rear = queue->_content;
            queue->_is_empty_flag = 1;
        }
    }
}
