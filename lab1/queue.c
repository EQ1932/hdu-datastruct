#include "queue.h"

q* create_q(int size)
{
    q* queue = (q*)malloc(sizeof(q));
    queue->data = (int*)malloc(sizeof(int) * size);
    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
    return queue;
}

bool is_full_q(q* queue)
{
    return (queue->rear + 1) % queue->size == queue->front;
}

bool is_empty_q(q* queue)
{
    return queue->front == queue->rear;
}

void push_q(q* queue, int data)
{
    if (is_full_q(queue))
    {
        printf("Queue is full\n");
        return;
    }
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->size;
}

int pop_q(q* queue)
{
    if (is_empty_q(queue))
    {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    return data;
}

void free_q(q* queue)
{
    free(queue->data);
    free(queue);
}