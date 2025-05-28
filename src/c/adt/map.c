// #include "../../header/adt/map.h"
// #include <stdlib.h>
// #include "../header/random.h"

// void map_create(Map t, int key,int room){
//     t->key = key;
//     t->prior = random_lcg(key,key);
//     t->value = room;
//     t->l = NULL;
//     t->r = NULL;
// }

// Map map_findMap(Map t,int key){
//     /* Jika t == NULL, maka key tidak ditemukan */
//     if( t == NULL ) {
//         return NULL;
//     }
//     /* Jika key sama, berarti prior ditemukan */
//     if( t->key == key ) return t;

//     if( key < t->key ) return map_findMap(t->l,key);
//     else return map_findMap(t->r,key);
// }

// void map_split(Map t, int key, pMap l, pMap r) {
//     /* Jika sampai di leaf, berhenti*/
//     if (t == NULL){
//         *l = NULL;
//         *r = NULL;
//     }
//     /* Jika key sekarang <= key_param split child kanan */
//     else if (t->key <= key){
//         map_split(t->r, key, &t->r, r);
//         *l = t;
//     }
//     /* Jika key sekarang > key_param split child kiri */
//     else{
//         map_split(t->l, key, l, &t->l);
//         *r = t;
//     }
// }

// void map_insertNewMap(pMap t, Map it){
//     /* Jika berada di akhir tree, buat node baru*/
//     if ( (*t) == NULL) *t = it;
    
//     /*  
//         Jika priority node sekarang > priority node baru:
//         Split tree menjadi 2 bagian:
//         1. tree dengan node key < key node baru
//         2. tree dengan node key >= key node baru
//         Kemudian, gabungkan kedua tree menjadi subtree dari node baru
//     */
//     else if (it->prior > (*t)->prior){
//         map_split(*t, it->key, &it->l, &it->r);
//         *t = it;
//     }
    
//     /*
//         Jika key node sekarang <= key node baru, traverse ke node kanan
//         Jika tidak, traverse ke node kiri
//     */
//     else{
//         if( (*t)->key <= it->key ) map_insertNewMap(&(*t)->r, it);
//         else map_insertNewMap(&(*t)->l, it);
//     }
// }

// void map_insertData(pMap t, int idDokter, int idPasien, int room) {
//     /* Jika tidak terdapat map dengan id yang sesuai, buat node map baru*/
//     if (*t == NULL) {
//         *t = malloc(sizeof(NodeMap));
//         map_create(*t, idDokter, room);
//         queue_push(&((*t)->data), idPasien);
//         return;
//     }LOGIN

//     /* Cari posisi map dengan id yang sesuai*/
//     Map mp = map_findMap(*t, idDokter);

//     /* Jika tidak terdapat map dengan id sesuai, buat node baru*/
//     if (mp == NULL) {
//         Map newMap = malloc(sizeof(NodeMap));
//         map_create(newMap, idDokter, room);
//         map_insertNewMap(t, newMap);
//         mp = newMap;
//     }
    
//     /* Push data baru ke queue berdasarkan posisi map yang sesuai*/
//     queue_push(&(mp->data), idPasien);
// }

// void map_popData(Map t,int idDokter){
//     Map mp = map_findMap(t,idDokter);
//     queue_pop(&(mp->data));
// }

#include "../../header/adt/map.h"
#include <stdlib.h>

void map_create(Map t, const char* room, int value){
    strcpy(t->key, room);
    t->prior = random_lcg((int)room[0],(int)room[1]);
    t->value = value;
    t->l = NULL;
    t->r = NULL;
}

Map map_findMap(Map t, const char* room){
    if (t == NULL) return NULL;
    int cmp = strcmp(room, t->key);
    if (cmp == 0) return t;
    else if (cmp < 0) return map_findMap(t->l, room);
    else return map_findMap(t->r, room);
}

void map_split(Map t, char* key, pMap l, pMap r) {
    if (t == NULL) {
        *l = NULL;
        *r = NULL;
    }
    else if (strcmp(t->key, key) <= 0) {
        map_split(t->r, key, &t->r, r);
        *l = t;
    }
    else {
        map_split(t->l, key, l, &t->l);
        *r = t;
    }
}

void map_insertNewMap(pMap t, Map it) {
    if (*t == NULL) {
        *t = it;
    }
    else if (it->prior > (*t)->prior) {
        // Split by room string
        map_split(*t, it->key, &it->l, &it->r);
        *t = it;
    }
    else {
        // Use strcmp for string comparison
        if (strcmp(it->key, (*t)->key) >= 0) {
            map_insertNewMap(&(*t)->r, it);
        } else {
            map_insertNewMap(&(*t)->l, it);
        }
    }
}

void map_insert(pMap t, char* key, int value){
    // Cek apakah key sekarang sudah disimpan pada map
    Map temp = map_findMap(*t, key);
    if( temp != NULL ) return;
    
    // Buat node baru
    Map newMap = malloc(sizeof(NodeMap));
    map_create(newMap, key, value);
    map_insertNewMap(t, newMap);
}