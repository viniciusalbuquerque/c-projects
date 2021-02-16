#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include "../node.h"

typedef struct queue {
    NODE* front;
} QUEUE;

NODE* queue_front(QUEUE* queue);
NODE* queue_back(QUEUE* queue);
void queue_push(QUEUE* queue, char elem);
void queue_pop(QUEUE* queue);
#endif
