#include "../../header/adt/set.h"

void set_create(Set t, int key){
    t->key = key;
    t->prior = random_lcg(key,key);
    t->l = NULL;
    t->r = NULL;
}

Set set_findSet(Set t,int key){
    /* Jika t == NULL, maka key tidak ditemukan */
    if( t == NULL ) {
        return NULL;
    }
    /* Jika key sama, berarti prior ditemukan */
    if( t->key == key ) return t;

    if( key < t->key ) return set_findSet(t->l,key);
    else return set_findSet(t->r,key);
}

void set_split(Set t, int key, pSet l, pSet r) {
    /* Jika sampai di leaf, berhenti*/
    if (t == NULL){
        *l = NULL;
        *r = NULL;
    }
    /* Jika key sekarang <= key_param split child kanan */
    else if (t->key <= key){
        set_split(t->r, key, &t->r, r);
        *l = t;
    }
    /* Jika key sekarang > key_param split child kiri */
    else{
        set_split(t->l, key, l, &t->l);
        *r = t;
    }
}

void set_insertNewSet(pSet t, Set it){
    /* Jika berada di akhir tree, buat node baru*/
    if ( (*t) == NULL) *t = it;
    
    /*  
        Jika priority node sekarang > priority node baru:
        Split tree menjadi 2 bagian:
        1. tree dengan node key < key node baru
        2. tree dengan node key >= key node baru
        Kemudian, gabungkan kedua tree menjadi subtree dari node baru
    */
    else if (it->prior > (*t)->prior){
        set_split(*t, it->key, &it->l, &it->r);
        *t = it;
    }
    
    /*
        Jika key node sekarang <= key node baru, traverse ke node kanan
        Jika tidak, traverse ke node kiri
    */
    else{
        if( (*t)->key <= it->key ) set_insertNewSet(&(*t)->r, it);
        else set_insertNewSet(&(*t)->l, it);
    }
}

void set_insertData(pSet t, int idDokter, int idPasien) {
    /* Jika tidak terdapat set dengan id yang sesuai, buat node set baru*/
    if (*t == NULL) {
        *t = malloc(sizeof(NodeSet));
        set_create(*t, idDokter);
        return;
    }

    /* Cari posisi set dengan id yang sesuai*/
    Set mp = set_findSet(*t, idDokter);

    /* Jika tidak terdapat set dengan id sesuai, buat node baru*/
    if (mp == NULL) {
        Set newSet = malloc(sizeof(NodeSet));
        set_create(newSet, idDokter);
        set_insertNewSet(t, newSet);
        mp = newSet;
    }
}