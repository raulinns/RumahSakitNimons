#ifndef OBAT_H
#define OBAT_H

#include "field.h"

#define id(x)                   (x).field[0]
#define nama_obat(x)            (x).field[1]
#define OBAT(l,x)               (l).contents[x]

typedef struct Obat{
    fields field[2];
} Obat;

typedef struct ObatList{
    Obat contents[MAX_USER];
    int len;
} ObatList;

#endif