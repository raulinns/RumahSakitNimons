#include "../../header/adt/set.h"
#include "string.h"

void set_create(Set t, char *key,int id){
    strcpy(t->key,key);
    t->prior = random_lcg(id,id);
    t->l = NULL;
    t->r = NULL;
}

Set set_findSet(Set t, char *key){
    if (t == NULL) return NULL;
    if (strcmp(t->key, key) == 0) return t;

    if (strcmp(t->key, key) > 0) 
        return set_findSet(t->l, key);
    else 
        return set_findSet(t->r, key);
}

void set_split(Set t, char *key, pSet l, pSet r) {
    /* Jika sampai di leaf, berhenti*/
    if (t == NULL){
        *l = NULL;
        *r = NULL;
    }
    /* Jika key sekarang <= key_param split child kanan */
    else if ( strcmp(t->key,key) <= 0 ){
        set_split(t->r, key, &t->r, r);
        *l = t;
    }
    /* Jika key sekarang > key_param split child kiri */
    else{
        set_split(t->l, key, l, &t->l);
        *r = t;
    }
}

int set_contains(Set t, char* key){
    Set iterator = set_findSet(t,key);
    if( iterator == NULL ) return 0;
    return 1;
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
        if( strcmp((*t)->key,it->key) <= 0 ) set_insertNewSet(&(*t)->r, it);
        else set_insertNewSet(&(*t)->l, it);
    }
}

void set_insertData(pSet t, char* name,int id) {
    /* Jika tidak terdapat set dengan id yang sesuai, buat node set baru*/
    if (*t == NULL) {
        *t = malloc(sizeof(NodeSet));
        set_create(*t, name,id);
        return;
    }

    /* Cari posisi set dengan id yang sesuai*/
    Set mp = set_findSet(*t, name);

    /* Jika tidak terdapat set dengan id sesuai, buat node baru*/
    if (mp == NULL) {
        Set newSet = malloc(sizeof(NodeSet));
        set_create(newSet, name, id);
        set_insertNewSet(t, newSet);
        mp = newSet;
    }
}