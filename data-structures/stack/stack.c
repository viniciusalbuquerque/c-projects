#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stack_push(STACK* stack, char elem) {
    NODE* newTop = malloc(sizeof(NODE));
    newTop->value = elem;
    newTop->next = stack->top;
    stack->top = newTop;
}

void stack_pop(STACK* stack) {
    if (!stack || !stack->top) {
        printf("Stack is empty. Cannot pop\n");
        return;
    }

    NODE* top = stack->top;
    stack->top = top->next;
    free(top);
}

char stack_top(STACK* stack) {
    if (!stack) {
        printf("Stack is empty. Cannot top\n");
        return '\0';
    }
    return stack->top->value;
}
