#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "../random.h"

/* ADT set yang digunakan memiliki struktur treap */
/* Setiap node pada treap memiliki key dan prior unik, dan menyimpan sebuah queue */

/*  Pendefinisian node set yang berisikan:
    key -> value yang disimpan
    prior -> prioritas node pada treap
    *l -> pointer ke node child dikiri
    *r -> pointer ke node child dikanan
*/
typedef struct NodeSet {
    char key[100];
    long prior;
    struct NodeSet *l, *r;
} NodeSet;

typedef NodeSet* Set;
typedef Set* pSet;

/* Membuat set baru dengan key sesuai parameter */
void set_create(Set t, char* key,int id);

/*
    Mengembalikan pointer ke node set dengan key sesuai parameter.
    Jika tree kosong atau node dengan key yang sesuai tidak ditemukan,
    maka akan dikembalikan NULL.
*/
Set set_findSet(Set t,char* key);

/*
    Melakukan split pada tree t, yang menghasilkan:
    - Tree l yang berisikan node d   21 | } NodeSet;
engan key <= key parameter
    - Tree r yang berisikan node dengan key > key parameter
    I.S. t adalah node yang valid, key adalah id yang valid
    F.S. Terbentuk tree l dan r sesuai kriteria diatas
*/
void set_split(Set t, char* key, pSet l, pSet r);

/*
    Menyisipkan node set baru pada ADT set.
    I.S. Set terinisialisasi
    F.S. ADT Set berisi node baru, yakni node *it 
*/
void set_insertNewSet(pSet t, Set it);

/*
    Memasukkan id baru ke antrian berdasarkan idDokter
    I.S. idDokter valid
    F.S. antrian idDokter mendapatkan data baru di akhir antrian
*/
void set_insertData(pSet t,char *name,int id);

#endif