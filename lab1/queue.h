#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// queue
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
}q;

q *create_q(int size);
void push_q(q *q, int data);
int pop_q(q *q);
bool is_empty_q(q *q);
bool is_full_q(q *q);
void free_q(q *q);