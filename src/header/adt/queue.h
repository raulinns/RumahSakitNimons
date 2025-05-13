#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "../file/user.h"
#include "node.h"

/* ADT Queue ini menyimpan antrian pasien*/

typedef struct Queue{
    struct Node* front;
    struct Node* tail;
    int size;
} Queue;

/* Membuat node baru yang berisikan data dari parameter */
void queue_create(Queue* head);

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

/* Output data pada queue mulai dari indeks terdepan*/
void queue_print(Queue* q);

#endif