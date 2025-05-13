#ifndef OBATPENYAKIT_H
#define OBATPENYAKIT_H

#include "field.h"

#define id(x)                   (x).fields[0]
#define penyakit_id(x)          (x).fields[1]
#define urutan(x)               (x).fields[2]
#define OBATPENYAKIT(l,x)       (l).contents[x]

typedef struct ObatPenyakit{
    fields field[3];
} ObatPenyakit;

typedef struct ObatPenyakitList{
    ObatPenyakit contents[MAX_USER];
} ObatPenyakitList;

#endif