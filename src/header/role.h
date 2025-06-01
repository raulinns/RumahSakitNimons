#ifndef ROLE_H
#define ROLE_H

#include "adt/queue.h"
#include "adt/list.h"

#define DOKTER(i) dokterList.contents[i]
#define PASIEN(i) pasienList.contents[i]
#define MANAGER(i) managerList.contents[i]

/* Defenisi role */

typedef struct _Manager{
    int id;
} _Manager;

typedef struct _Dokter{
    int id;
    int aura;
    char ruangKerja[3];
    char spesialisasi[100];
    Queue* antrian;
    int queue_size;
} _Dokter;


typedef struct _Pasien{
    int id;
    int idDokter;
    int sudahDiagnosis;
} _Pasien;

/* Bentukan list dari role */

typedef struct ManagerList{
    _Manager contents[MAX_USER];
    int neff;
} ManagerList;


typedef struct DokterList{
    _Dokter contents[MAX_USER];
    int neff;
} DokterList;


typedef struct PasienList{
    _Pasien contents[MAX_USER];
    int neff;
} PasienList;

extern DokterList dokterList;
extern PasienList pasienList;
extern ManagerList managerList;

/* MODUL SPESIFIK UNTUK PASIEN */

void AddPasienList(int id);

/* MODUL SPESIFIK UNTUK DOKTER */

void AddPasien_to_Dokter(int idPasien,int idDokter);

int DokterList_NametoID(char* name);

void AddDokterList(int id);

void AssignDokter();

int UserID_to_DokterID(int id);

/* MODUL SPESIFIK UNTUK MANAGER */

void AddManagerList(int id);

#endif