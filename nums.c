#include <stdlib.h>
#include <stdio.h>
#include "nums.h"

num_stack* stack_push(num_stack *s, num_node *n){
    s->tail = n;
    s->next = (num_stack*)malloc(sizeof(num_stack));
    s->next->prev = s;
    s = s->next;
    s->num_sign = 1;
    s->num_len = 0;
    s->stack_size = s->prev->stack_size + 1;
    s->next = 0;
    return s;
}

num_stack* stack_pop(num_stack *s){
    if(s->prev == 0){
        printf("empty stack\n");
        return s;
    }
    s = s->prev;
    s->head = 0;
    s->tail = 0;
    s->num_sign = 1;
    s->num_len = 0;
    s->next = 0;
    return s;
}
