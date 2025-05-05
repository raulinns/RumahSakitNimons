#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct Queue{
    struct Node* front;
    struct Node* tail;
    int size;
} Queue;

/* Membuat node baru yang berisikan data dari parameter */
Queue* queue_create();

/* Menambahkan node baru di queue */
void queue_push(Queue* head, int data);

/* Mengembalikan pointer ke posisi terdepan pada queue
   Mengembalikan NULL jika queue kosong
*/
Node* queue_front(Queue* head);

/* Menghapus elemen terdepan pada queue */
void queue_pop(Queue* head);

/* Menghapus queue seluruhnya */
void queue_clear(Queue* q);

/* Mengembalikan 1 jika queue kosong
   Mengembalikan 0 jika queue memiliki setidaknya satu elemen*/
int queue_isEmpty(Queue q);

#endif