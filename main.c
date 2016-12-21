#include <stdio.h>
#include <stdlib.h>
#include "nums.h"
#include "arithmetic.h"


void main(){
    char c;
    num_stack *stack = (num_stack*)malloc(sizeof(num_stack));
    stack->num_sign = 1;
    stack->num_len = 0;
    stack->stack_size = 0;
    stack->prev = 0;
    stack->prev = 0;
    num_node *tail = 0;

    while(1){
        c = getc(stdin);
        switch(c){
            case '+':
                c = getc(stdin);
                num_stack *a = stack->prev->prev;
                num_stack *b = stack->prev;
                if(a->num_sign == b->num_sign){
                    num_stack *cur_stack;
                    if(cmp(a, b))
                        cur_stack = addition(a, b);
                    else
                        cur_stack = addition(b, a);
                    stack = stack_pop(stack);
                    stack = stack_pop(stack);
                    if(a->num_sign == 0) stack->num_sign = 0;
                    stack->head = cur_stack->head;
                    stack->num_len = cur_stack->num_len;
                    stack = stack_push(stack, cur_stack->tail);
                } else {
                    num_stack *cur_stack;
                    if(cmp(a, b)){
                        char cur_sign = a->num_sign;
                        cur_stack = substraction(a, b);
                        stack = stack_pop(stack);
                        stack = stack_pop(stack);
                        stack->num_sign = cur_sign;
                    } else {
                        cur_stack = substraction(b, a);
                        char cur_sign = b->num_sign;
                        stack = stack_pop(stack);
                        stack = stack_pop(stack);
                        stack->num_sign = cur_sign;
                    }
                        stack->head = cur_stack->head;
                        stack->num_len = cur_stack->num_len;
                        stack = stack_push(stack, cur_stack->tail);
                }
                break;

            case '-':
                c = getc(stdin);
                if(c != '\n'){
                    if(c != 48) stack->num_sign = 0;
                    goto nega;
                }else{

                }
                break;

            //case '*':
            //    c = getc(stdin);

            //case '/';
            //    c = getc(stdin);

            case '=':
                c = getc(stdin);
                if(stack->prev == 0){
                    printf("empty stack\n");
                    break;
                }
                num_node *out = stack->prev->head;
                if(stack->prev->num_sign == 0) printf("-");
                while(out->next != 0){
                    printf("%d", out->x);
                    out = out->next;
                }
                printf("%d, %d\n", out->x, stack->prev->num_len);
                break;

            case '\n':
                while(stack->head->x == 0 && stack->head != tail){
                    stack->head = stack->head->next;
                    stack->head->prev = 0;
                    stack->num_len -= 1;
                }
                stack = stack_push(stack, tail);
                tail = 0;
                break;

            case 'p':
                c = getc(stdin);
                stack = stack_pop(stack);
                break;

            case 'q':
                return;

            default:
                nega: ;
                num_node *tmp = (num_node*)malloc(sizeof(num_node));
                tmp->x = c-48;
                tmp->prev = tail;
                tmp->next = 0;
                if(tail != 0) tail->next = tmp;
                else stack->head = tmp;
                tail = tmp;
                stack->num_len += 1;
                break;
        }
    }
}
