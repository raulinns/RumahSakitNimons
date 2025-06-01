#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "../random.h"

/* ADT set yang digunakan memiliki struktur treap */
/* Setiap node pada treap memiliki key (kode ruang) dan prior unik, dan menyimpan sebuah idDokter */

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

/* Membuat node set baru dengan key dan prioritas berdasarkan id */
void set_create(Set t, char *key, int id);

/* Mencari node set dengan key tertentu dalam tree t */
Set set_findSet(Set t, char *key);

/* Memisahkan tree t menjadi dua tree berdasarkan key:
   - l: tree dengan key <= key parameter
   - r: tree dengan key > key parameter
*/
void set_split(Set t, char *key, pSet l, pSet r);

/* Mengecek apakah tree t mengandung key tertentu.
   Mengembalikan 1 jika ada, 0 jika tidak.
*/
int set_contains(Set t, char* key);

/* Menyisipkan node baru it ke dalam tree t dengan mempertimbangkan prioritas */
void set_insertNewSet(pSet t, Set it);

/* Menyisipkan data baru berupa nama dan id ke dalam tree t.
   Jika key belum ada, membuat node baru dan menyisipkannya.
*/
void set_insertData(pSet t, char* name, int id);

#endif