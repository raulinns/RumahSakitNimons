#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

typedef struct LinkedList{
    struct Node* head;
    struct Node* tail;
    int size;
} LinkedList;

/* Membuat linked list baru */
LinkedList* linked_create();

/* Menambahkan node baru di akhir list */
void linked_insertEnd(LinkedList* head, int data);

/* Mengoutput isi dari list dari posisi head ke tail */
void linked_print(LinkedList head);

/* Menghapus list */
void linked_free(LinkedList* head);

/* Mengembalikan 1 jika stack kosong
   Mengembalikan 0 jika stack memiliki setidaknya satu elemen*/
int linked_isEmpty(LinkedList head);

/* Menghapus elemen ke-x di linked-list 
   NOTE : zero based indexing */
void linked_delete(LinkedList* head,int idx);

#endif