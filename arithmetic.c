#include <stdio.h>
#include <stdlib.h>
#include "arithmetic.h"
#include "nums.h"

int cmp(num_stack *a, num_stack *b){
    if(a->num_len == b->num_len){
        while(a->head->x == b->head->x && a->head->next != 0){
            a->head = a->head->next;
            b->head = b->head->next;
        }
        if(a->head->x > b->head->x) return 1;
        else return 0;
    }
    return (a->num_len > b->num_len);
}

num_stack* addition(num_stack *a, num_stack *b){
    unsigned int bs = b->num_len;
    num_node *head = a->tail;
    num_stack *out = (num_stack*)malloc(sizeof(num_stack));
    out->num_len = a->num_len;
    char cur;

    while(bs){
        cur = head->x + b->tail->x;
        head->x = cur % 10;
        if(head->prev != 0){
            head->prev->x += (cur / 10);
            head = head->prev;
        }
        if(b->tail->prev != 0) b->tail = b->tail->prev;
        --bs;
    }

    if(cur / 10 == 1 && a->num_len == b->num_len){
        head->prev = (num_node*)malloc(sizeof(num_node));
        head->prev->next = head;
        head = head->prev;
        head->x = 1;
        head->prev = 0;
        out->num_len += 1;
    }
    while(head->prev != 0)
        head = head->prev;

    out->head = head;
    out->tail = a->tail;

    return out;
}

num_stack* substraction(num_stack *a, num_stack* b){
    unsigned int bs = b->num_len;
    num_node *head = a->tail;
    num_stack *out = (num_stack*)malloc(sizeof(num_stack));
    out->num_len = a->num_len;
    char cur;

    while(bs){
        if(head->x < b->tail->x){
            cur = head->x + 10 - b->tail->x;
            head->x = cur;
            head->prev->x -= 1;
        } else {
            cur = head->x - b->tail->x;
            head->x = cur;
        }
        if(head->prev != 0){
            head = head->prev;
        }
        if(b->tail->prev != 0) b->tail = b->tail->prev;
        --bs;
    }
    while(head->prev != 0)
        head = head->prev;

    while(head->x == 0 && head != a->tail){
        head = head->next;
        head->prev = 0;
        out->num_len -= 1;
    }

    out->head = head;
    out->tail = a->tail;

    return out;
}
