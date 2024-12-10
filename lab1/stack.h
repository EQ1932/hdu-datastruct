#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// stack

typedef struct {
    int *data;
    int top; //top means used size
    int size;
} stack;

stack *create_stack(int size);
void push_stack(stack *s, int data);
int pop_stack(stack *s);
bool is_empty_stack(stack *s);
bool is_full_stack(stack *s);
void free_stack(stack *s);