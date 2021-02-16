#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include "../node.h"

typedef struct stack {
    NODE* top;
} STACK;

void stack_push(STACK* stack, char element);
void stack_pop(STACK* stack);
char stack_top(STACK* stack);
#endif
