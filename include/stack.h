#ifndef STACK_H
#define STACK_H

typedef struct stack {
    char *top;
    long len;
    long max;
} stack;

void stack_push_c(stack *s, char c);

#endif