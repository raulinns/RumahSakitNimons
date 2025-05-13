#ifndef OBATPENYAKIT_H
#define OBATPENYAKIT_H

#include "field.h"

#define MAX_FIELDS 3

#define id(x)                   (x).fields[0]
#define penyakit_id(x)          (x).fields[1]
#define urutan(x)               (x).fields[2]
#define OBATPENYAKIT(l,x)       (l).contents[x]

typedef struct ObatPenyakit{
    fields field[MAX_FIELDS];
} ObatPenyakit;

typedef struct ObatPenyakitList{
    ObatPenyakit contents[MAX_USER];
} ObatPenyakitList;

#endif