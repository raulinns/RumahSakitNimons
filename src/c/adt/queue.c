#include "../../header/adt/queue.h"

void queue_create(Queue* q){
    q->size = 0;
    q->front = NULL;
    q->tail = NULL;
}

void queue_push(Queue* q, int data){
    Node* newNode = createNode(data);
    if (q->front == NULL) {
        q->front = newNode;
        q->tail = newNode;
        q->size = q->size + 1;;
        return;
    }
    q->tail->next = newNode;
    q->tail = newNode;
    q->size = q->size + 1;
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
    while( q->size > 0) queue_pop(q);
}

int queue_isEmpty(Queue q){
    return q.size == 0;
}

void queue_print(Queue* q) {
    if (queue_isEmpty(*q)) {
        //printf("Queue kosong.\n");
        return;
    }

    Node* current = q->front;
    printf("Isi queue (%d item):\n", q->size);
    int i = 1;
    while (current != NULL) {
        printf("%d ", current->data); //
        current = current->next;
        i++;
    }
    printf("\n");
}
