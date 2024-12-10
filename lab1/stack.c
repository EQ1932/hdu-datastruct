#include "stack.h"

stack* create_stack(int size)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = (int *)malloc(size * sizeof(int));
    s->top = -1;
    s->size = size;
    return s;
}

void push_stack(stack *s, int data)
{
    if (s->top == s->size - 1)
    {
        printf("stack is full\n");
        return;
    }
    s->top++;
    s->data[s->top] = data;
}   

int pop_stack(stack *s)
{
    if (s->top == -1)
    {
        printf("stack is empty\n");
        return -1;
    }
    int data = s->data[s->top];
    s->top--;
    return data;
}

bool is_empty_stack(stack *s)
{
    return s->top == -1;
}

bool is_full_stack(stack *s)
{
    return s->top == s->size - 1;
}

void free_stack(stack *s)
{
    free(s->data);
    free(s);
}

