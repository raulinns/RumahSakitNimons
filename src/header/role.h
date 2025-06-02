#ifndef ROLE_H
#define ROLE_H

#include "adt/queue.h"
#include "adt/list.h"

#define DOKTER(i) dokterList.contents[i]
#define PASIEN(i) pasienList.contents[i]
#define MANAGER(i) managerList.contents[i]

int userPosByID(int id);

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
    int sudahDiobati;
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

/** Mengembalikan indeks user dalam Ulist berdasarkan ID. 
 Jika tidak ditemukan, mengembalikan -1.
*/
int userPosByID(int id);

/** Mengubah UserID menjadi indeks pasien dalam pasienList. 
 Jika tidak ditemukan, mengembalikan -1.
*/
int UserID_to_PasienID(int id);

/**
  Menambahkan pasien baru ke pasienList dengan id tertentu
  I.S. : pasienList terdefinisi
  F.S. : pasien baru ditambahkan ke pasienList dengan atribut default
*/
void AddPasienList(int id);

/**
  Mengecek status antrian pasien berdasarkan id
  I.S. : pasienList dan dokterList terdefinisi, pasien dengan id harus ada
  F.S. : Menampilkan status antrian pasien atau pesan jika belum terdaftar antrian
*/
void CekAntrian(int id);

/**
  Prosedur pendaftaran pasien untuk check-up
  I.S. : pasien dengan masterID terdefinisi dan belum terdaftar antrian
  F.S. : Data check-up pasien tersimpan, pasien terdaftar pada antrian dokter
*/
void DaftarCheckup();

/**
  Menambahkan pasien ke antrian dokter tertentu
  I.S. : dokterList dan pasienList terdefinisi
  F.S. : Pasien dengan idPasien masuk antrian dokter dengan idDokter
*/
void AddPasien_to_Dokter(int idPasien,int idDokter);

/** Mengembalikan indeks dokter di dokterList berdasarkan UserID. 
 Jika tidak ditemukan, mengembalikan -1.
*/
int UserID_to_DokterID(int id);

/** Mengembalikan indeks dokter dalam dokterList berdasarkan nama pengguna (username). 
 Jika tidak ditemukan, mengembalikan -1.
*/
int DokterList_NametoID(char* name);

/**
  Menambahkan dokter baru ke dokterList dengan id tertentu
  I.S. : dokterList terdefinisi
  F.S. : Dokter baru ditambahkan ke dokterList dengan atribut default
*/
void AddDokterList(int id);

/**
  Menugaskan dokter ke ruangan tertentu
  I.S. : dokterList dan map RuangtoDokter terdefinisi
  F.S. : Dokter diassign ke ruangan jika valid, output pesan status
*/
void AssignDokter();

/**
  Menambahkan manager baru ke managerList dengan id tertentu
  I.S. : managerList terdefinisi
  F.S. : Manager baru ditambahkan ke managerList
*/
void AddManagerList(int id);


#endif