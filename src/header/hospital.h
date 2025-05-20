#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "adt/queue.h"

#define RUANGAN(x) ListRuangan(x);

typedef struct Ruangan{
    int idDokter;
    Queue antrean;
} Ruangan;

typedef struct ListRuangan{
    Ruangan ruangan[MAX_USER];
} ListRuangan;

#endif