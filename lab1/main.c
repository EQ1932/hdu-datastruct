#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

#define car_num 1005

int n;
stack *in;
stack *out;
q *waiting;

int a_t[1005];
int l_t[1005];

void init()
{
    in = create_stack(n);
    out = create_stack(n);
    waiting = create_q(car_num);
    memset(a_t, -1, sizeof(a_t));
    memset(l_t, -1, sizeof(l_t));
}

void arrive(int id, int car_time)
{
    if(is_full_stack(in))
    {
        push_q(waiting, id);
    }
    else
    {
        push_stack(in, id);
        a_t[id] = car_time;
    }
    printf("id: %d arrive: %d\n", id, car_time);
}

void departure(int id, int car_time)
{
    int now_id = -1;
    while(now_id != id)
    {
        now_id = pop_stack(in);
        //printf("now_id: %d\n", now_id);
        if(now_id != id)
        {
            push_stack(out, now_id);
        }
    }
    l_t[id] = car_time;
    while(!is_empty_stack(out))
    {
        now_id = pop_stack(out);
        push_stack(in, now_id);
    }
    while(!is_empty_q(waiting) && !is_full_stack(in))
    {
        now_id = pop_q(waiting);
        push_stack(in, now_id);
        a_t[now_id] = car_time;
    }
    printf("id: %d departure: %d\n", id, car_time);
}

void calc()
{
    for(int i = 0; i < car_num; i++)
    {
        if(a_t[i] != -1)
        {
            if(l_t[i] != -1)
            {
                printf("id: %d arrive: %d departure: %d stay: %d\n", i, a_t[i], l_t[i], l_t[i] - a_t[i]);
            }
            else 
            {
                printf("id: %d arrive: %d departure: NONE stay: still staying\n", i, a_t[i]);
            }
        }
    }
}

int main()
{
    scanf("%d\n", &n);
    init();
    while(1)
    {
        char type;
        int id, car_time;
        scanf("%c %d %d", &type, &id, &car_time);
        //printf("type: %c id: %d time: %d\n", type, id, car_time);
        if(type == 'E')
        {
            printf("OVER\n");
            break;
        }
        else if(type == 'A')
        {
            arrive(id, car_time);
        }
        else if(type == 'D')
        {
            departure(id, car_time);
        }
    }
    calc();
}