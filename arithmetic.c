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

num_stack* addit(num_stack *a, num_stack *b){
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

num_stack* subst(num_stack *a, num_stack* b){
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

num_stack* multi(num_stack *a, num_stack *b){
    unsigned int as = a->num_len, bs = b->num_len;
    if(bs == 1){
        num_node *head = a->tail;
        num_stack *cur_stack = (num_stack*)malloc(sizeof(num_stack));
        cur_stack->num_len = a->num_len;
        char cur, r = 0;

        while(as){
            cur = head->x * b->tail->x + r;
            head->x = cur % 10;
            r = cur / 10;
            if(head->prev != 0) head = head->prev;
            --as;
        }
        if(r){
            head->prev = (num_node*)malloc(sizeof(num_node));
            head->prev->next = head;
            head = head->prev;
            head->prev = 0;
            head->x = r;
            cur_stack->num_len += 1;
        }
        while(head->x == 0 && head != a->tail){
            head = head->next;
            head->prev = 0;
            cur_stack->num_len -= 1;
        }
        cur_stack->head = head;
        cur_stack->tail = a->tail;
        return cur_stack;
    }

    num_stack *a1 = (num_stack*)malloc(sizeof(num_stack)),
            *b1 = (num_stack*)malloc(sizeof(num_stack));
    a1->tail = (num_node*)malloc(sizeof(num_node));
    a1->num_len = a->num_len + 1;
    b1->tail = (num_node*)malloc(sizeof(num_node));
    b1->num_len = b->num_len - 1;
    num_node *cur1 = a->head, *cur2 = b->head;
    while(cur1->next){
        a1->tail->x = cur1->x;
        a1->tail->next = (num_node*)malloc(sizeof(num_node));
        a1->tail->next->prev = a1->tail;
        a1->tail = a1->tail->next;
        cur1 = cur1->next;
    }
    a1->tail->x = cur1->x;
    a1->tail->next = (num_node*)malloc(sizeof(num_node));
    a1->tail->next->prev = a1->tail;
    a1->tail = a1->tail->next;
    a1->tail->x = 0;

    while(cur2->next){
        b1->tail->x = cur2->x;
        b1->tail->next = (num_node*)malloc(sizeof(num_node));
        b1->tail->next->prev = b1->tail;
        b1->tail = b1->tail->next;
        cur2 = cur2->next;
    }

    b->num_len = 1;


    //printf("a) %d, b) %d\n", a->num_len, b->num_len);
/*
    num_node *out1 = a->head, *out2 = b->head, *out3 = a1->tail, *out4 = b1->tail;

    printf("a) ");
    while(as){
        printf("%d", out1->x);
        out1 = out1->next;
        --as;
    }
    printf("\nb) ");
    while(bs){
        printf("%d", out2->x);
        out2 = out2->next;
        --bs;
    }
    as = a1->num_len; bs = b1->num_len;
    printf("\na1) ");
    while(as){
        printf("%d", out3->x);
        out3 = out3->prev;
        --as;
    }
    printf("\nb1) ");
    while(bs){
        printf("%d", out4->x);
        out4 = out4->prev;
        --bs;
    }
*/

    return addit(multi(a1, b1), multi(a, b));
}
