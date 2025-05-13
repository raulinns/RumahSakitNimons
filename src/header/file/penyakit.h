#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "field.h"

#define MAX_FIELDS 20

#define id(x)               (x).fields[0]
#define penyakit(x)         (x).fields[1]
#define suhu_min(x)         (x).fields[2]
#define suhu_max(x)         (x).fields[3]
#define sistol_min(x)       (x).fields[4]
#define sistol_max(x)       (x).fields[5]
#define diastol_min(x)      (x).fields[6]
#define diastol_max(x)      (x).fields[7]
#define detak_min(x)        (x).fields[8]
#define detak_max(x)        (x).fields[9]
#define saturasi_min(x)     (x).fields[10]
#define saturasi_max(x)     (x).fields[11]
#define gula_min(x)         (x).fields[12]
#define gula_max(x)         (x).fields[13]
#define berat_min(x)        (x).fields[14]
#define berat_max(x)        (x).fields[15]
#define tinggi_min(x)       (x).fields[16]
#define tinggi_max(x)       (x).fields[17]
#define trombosit_min(x)    (x).fields[18]
#define trombosit_max(x)    (x).fields[19]
#define PENYAKIT(l,x)       (l).contents[x]

typedef struct Penyakit{
    fields field[MAX_FIELDS];
} Penyakit;

typedef struct PenyakitList{
    Penyakit contents[MAX_USER];
} PenyakitList;

#endif