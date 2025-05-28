#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "field.h"

#define id(x)               (x).field[0]
#define penyakit(x)         (x).field[1]
#define suhu_min(x)         (x).field[2]
#define suhu_max(x)         (x).field[3]
#define sistol_min(x)       (x).field[4]
#define sistol_max(x)       (x).field[5]
#define diastol_min(x)      (x).field[6]
#define diastol_max(x)      (x).field[7]
#define detak_min(x)        (x).field[8]
#define detak_max(x)        (x).field[9]
#define saturasi_min(x)     (x).field[10]
#define saturasi_max(x)     (x).field[11]
#define gula_min(x)         (x).field[12]
#define gula_max(x)         (x).field[13]
#define berat_min(x)        (x).field[14]
#define berat_max(x)        (x).field[15]
#define tinggi_min(x)       (x).field[16]
#define tinggi_max(x)       (x).field[17]
#define trombosit_min(x)    (x).field[18]
#define trombosit_max(x)    (x).field[19]
#define PENYAKIT(l,x)       (l).contents[x]

typedef struct Penyakit{
    fields field[20];
} Penyakit;

typedef struct PenyakitList{
    Penyakit contents[MAX_USER];
    int len;
} PenyakitList;

#endif