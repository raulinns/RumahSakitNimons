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

/**
 Membuat linked list kosong
 I.S. : newLinked sembarang
 F.S. : newLinked menjadi linked list kosong
*/
void linked_create(LinkedList* newLinked);

/**
 Menambahkan elemen di akhir linked list
 I.S. : list mungkin kosong atau berisi elemen
 F.S. : Elemen data ditambahkan di akhir list
*/
void linked_insertEnd(LinkedList* list, int data);

/**
 Mencetak semua elemen linked list
 I.S. : list mungkin kosong atau berisi elemen
 F.S. : Semua elemen dicetak ke output
*/
void linked_print(LinkedList list);

/**
 Membebaskan memori semua node dalam linked list
 I.S. : list mungkin berisi elemen
 F.S. : Semua node dibebaskan dan list kosong
*/
void linked_free(LinkedList* list);

/**
 Mengecek apakah linked list kosong
 Return : 1 jika kosong, 0 jika tidak
*/
int linked_isEmpty(LinkedList head);

/**
 Menghapus elemen pada indeks tertentu
 I.S. : idx < size list
 F.S. : Elemen pada indeks idx dihapus dan ukuran list berkurang
*/
void linked_delete(LinkedList* head, int idx);


#endif