#include "../../header/adt/stack.h"

void stack_create(Stack* s){
    s->size = 0;
    s->top = NULL;
}

void stack_push(Stack* s, int data){
    struct Node* newNode = createNode(data);
    if (s->top == NULL) {
        s->top = newNode;
        s->size = s->size + 1;
        return;
    }
    newNode->next = s->top;
    s->top = newNode;
    s->size = s->size + 1;
}

Node* stack_top(Stack* s){
    return s->top;
}

void stack_pop(Stack* s){
    if( s->size == 0 ){
        return;
    }
    s->size = s->size - 1;
    Node* temp = s->top;
    s->top = temp->next;
    free(temp);
}

int stack_isEmpty(Stack s){
    return s.size == 0;
}

void stack_clear(Stack* s){
    while( s->size > 0 ) stack_pop(s);
}