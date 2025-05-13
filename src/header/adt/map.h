#ifndef MAP_H
#define MAP_H

#include "queue.h"
/* ADT map yang digunakan memiliki struktur treap */
/* Setiap node pada treap memiliki key dan prior unik, dan menyimpan sebuah queue */

typedef struct NodeMap {
    int key;
    int room;
    long prior;
    Queue data;
    struct NodeMap *l, *r;
} NodeMap;

typedef NodeMap* Map;
typedef Map* pMap;

/* Membuat map baru dengan key sesuai parameter */
void map_create(Map t, int key, int room);

/*
    Mengembalikan pointer ke node map dengan key sesuai parameter.
    Jika tree kosong atau node dengan key yang sesuai tidak ditemukan,
    maka akan dikembalikan NULL.
*/
Map map_findMap(Map t,int key);

/*
    Melakukan split pada tree t, yang menghasilkan:
    - Tree l yang berisikan node dengan key <= key parameter
    - Tree r yang berisikan node dengan key > key parameter
    I.S. t adalah node yang valid, key adalah id yang valid
    F.S. Terbentuk tree l dan r sesuai kriteria diatas
*/
void map_split(Map t, int key, pMap l, pMap r);

/*
    Menyisipkan node map baru pada ADT map.
    I.S. Map terinisialisasi
    F.S. ADT Map berisi node baru, yakni node *it 
*/
void map_insertNewMap(pMap t, Map it);

/*
    Memasukkan id baru ke antrian berdasarkan idDokter
    I.S. idDokter valid
    F.S. antrian idDokter mendapatkan data baru di akhir antrian
*/
void map_insertData(pMap t, int idDokter, int idPasien,int room);

/*
    Melakukan operasi pop pada antrian yang berisikan
    pasien dari dokter dengan idDokter.
    I.S Antrian idDokter tidak boleh koson
    F.S Pasien di posisi terdepan keluar dari antrian
*/
void map_popData(Map t,int idDokter);


#endif