#include "../include/stack.h"

void stack_push_c(stack *s, char c)
{
    if (s->len >= s->max) {
        return;
    }

    *s->top = c;
    s->top++;
    s->len++;
}