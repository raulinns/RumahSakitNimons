#include "../header/adt/queue.h"

Queue* queue_create(){
    Queue* newQueue = malloc(sizeof(Queue));
    if (!newQueue) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newQueue->front = NULL;
    newQueue->tail = NULL;
    return newQueue;
}

void queue_push(Queue* q, int data){
    struct Node* newNode = createNode(data);
    if (q->front == NULL) {
        q->front = newNode;
        return;
    }
    q->tail->next = newNode;
    q->tail = newNode;
    q->size++;
}

Node* queue_front(Queue* q){
    return q->front;
}

void queue_pop(Queue* q){
    if( q->size == 0 ){
        return;
    }
    q->size = q->size - 1;
    Node* temp = q->front;
    Node* nxt = temp->next;
    q->front = nxt;
    free(temp);
}

void queue_clear(Queue* q){
    Node* cur = q->front;
    Node* temp;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(q);
}

int queue_isEmpty(Queue q){
    return q.size == 0;
}