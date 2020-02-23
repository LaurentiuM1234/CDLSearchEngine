#ifndef _QUEUE_H

#define _QUEUE_H

#include "structs.h"
#define QUEUE_EMPTY(queue) (queue->_is_empty_flag)
#define QUEUE_FULL(queue) (queue->_front == queue->_content + queue->_field_size * queue->_content_size)



TQueue *createQueue(size_t field_size, size_t content_size);
void pushQueue(void *item, TQueue *queue);
void popQueue(TQueue *queue);



#endif
