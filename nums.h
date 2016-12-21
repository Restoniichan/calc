#pragma once

typedef struct num_node {
    char x;
    struct num_node *prev;
    struct num_node *next;
} num_node;

typedef struct num_stack {
    num_node *head;
    num_node *tail;
    char num_sign;
    unsigned int num_len;

    unsigned int stack_size;
    struct num_stack *prev;
    struct num_stack *next;
} num_stack;

num_stack* stack_push(num_stack *s, num_node *n);
num_stack* stack_pop(num_stack *s);
