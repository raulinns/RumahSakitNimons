#include "../../header/adt/list.h"
#include "string.h"

void list_create(List *l) {
    NEFF(*l) = 0;
}

void list_add(List *l,char *name){
    strcpy(l->contents[l->nEff],name);
    l->nEff = l->nEff + 1;
}