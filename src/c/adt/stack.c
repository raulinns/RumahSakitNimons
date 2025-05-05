#include "../header/adt/stack.h"

Stack* stack_create(){
    Stack* newStack = malloc(sizeof(Stack));
    if (!newStack) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newStack->top = NULL;
    return newStack;
}

void stack_push(Stack* s, int data){
    struct Node* newNode = createNode(data);
    if (s->top == NULL) {
        s->top = newNode;
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