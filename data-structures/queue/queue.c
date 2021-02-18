#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

NODE* queue_front(QUEUE* queue) {
    if (!queue) {
        printf("Queue should not be null");
        exit(1);
    }
    return queue->front;
}

NODE* queue_back(QUEUE* queue) {
    if (!queue) {
        printf("Queue should not be null");
        exit(1);
    }

    NODE* node = queue_front(queue);
    if (!node) {
        printf("Empty queue.\n");
        return NULL;
    }

    while (node->next) {
        node = node->next;
    }
    return node;
}

void queue_push(QUEUE* queue, char elem) {
    NODE* node = malloc(sizeof(NODE));
    node->value = elem;
    node->next = NULL;

    if(!queue_front(queue)) {
        queue->front = node;
    } else {
        NODE* back = queue_back(queue);
        back->next = node;
    }
}

void queue_push_node(QUEUE* queue, NODE* node) {
    if (!queue_front(queue)) {
        queue->front = node;
    } else {
        queue_back(queue)->next = node;
    }
}

void queue_pop(QUEUE* queue) {
    NODE* front = queue_front(queue);
    if (!front) {
        printf("Queue is empty. Cannot pop\n");
        return;
    }
    queue->front = front->next;
    free(front);
}
    
/*int main() {
    QUEUE queue = { NULL };
    queue_pop(&queue);
    queue_push(&queue, 'a');
    queue_push(&queue, 'b');

    printf("front: %c. back: %c\n", queue_front(&queue)->value, queue_back(&queue)->value);
    queue_pop(&queue);
    printf("front: %c. back: %c\n", queue_front(&queue)->value, queue_back(&queue)->value);

}*/
