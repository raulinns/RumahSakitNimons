#ifndef OBAT_H
#define OBAT_H

#include "field.h"

#define MAX_FIELDS 2

#define id(x)                   (x).fields[0]
#define nama_obat(x)            (x).fields[1]
#define OBAT(l,x)               (l).contents[x]

typedef struct Obat{
    fields field[MAX_FIELDS];
} Obat;

typedef struct ObatList{
    Obat contents[MAX_USER];
} ObatList;

#endif