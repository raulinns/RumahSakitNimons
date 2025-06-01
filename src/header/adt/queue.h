#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "../file/ext-list.h"
#include "node.h"

/* ADT Queue ini menyimpan antrian pasien*/

typedef struct Queue{
    struct Node* front;
    struct Node* tail;
    int size;
} Queue;


/**
 Membuat queue kosong
 I.S. : Queue q sembarang (mungkin belum terisi)
 F.S. : Queue q terinisialisasi sebagai queue kosong
*/
void queue_create(Queue* q);

/**
 Menambahkan elemen ke belakang queue
 I.S. : Queue q mungkin kosong atau berisi
 F.S. : Elemen data ditambahkan ke belakang queue
*/
void queue_push(Queue* q, int data);

/**
 Mengembalikan pointer ke elemen paling depan queue
 Return : Node* yang menunjuk ke front, atau NULL jika kosong
*/
Node* queue_front(Queue* q);

/**
 Menghapus elemen paling depan queue
 I.S. : Queue q tidak kosong
 F.S. : Elemen paling depan queue dihapus, ukuran queue berkurang 1
*/
void queue_pop(Queue* q);

/**
 Menghapus semua elemen dalam queue
 I.S. : Queue q mungkin berisi elemen atau kosong
 F.S. : Queue q menjadi kosong, semua elemen dibebaskan
*/
void queue_clear(Queue* q);

/**
 Mengecek apakah queue kosong
 Return : 1 jika kosong, 0 jika tidak
*/
int queue_isEmpty(Queue q);

/**
 Mencetak semua elemen dalam queue
 I.S. : Queue q mungkin kosong atau berisi
 F.S. : Semua elemen queue dicetak ke output
*/
void queue_print(Queue* q);

#endif