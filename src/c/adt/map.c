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

void map_delete(pMap t, const char* key) {
    if (*t == NULL) return;

    int cmp = strcmp(key, (*t)->key);
    if (cmp == 0) {
        Map temp = *t;
        map_merge(t, (*t)->l, (*t)->r);
        free(temp);
    } else if (cmp < 0) {
        map_delete(&(*t)->l, key);
    } else {
        map_delete(&(*t)->r, key);
    }
}

void map_merge(pMap t, Map l, Map r) {
    if (l == NULL && r == NULL) {
        *t = NULL;
        return;
    }

    if (l == NULL) {
        *t = r;
        return;
    }

    if (r == NULL) {
        *t = l;
        return;
    }

    if (l->prior > r->prior) {
        map_merge(&l->r, l->r, r);
        *t = l;
    } else {
        map_merge(&r->l, l, r->l);
        *t = r;
    }
}