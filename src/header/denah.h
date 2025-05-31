#ifndef DENAH_H
#define DENAH_H

#include "../header/adt/matrix.h"
#include "../header/adt/list.h"

#define MAT(d) (d).M
#define LIST(d) (d).l

typedef struct Denah{
   Matrix M;
   List l;
   int maxPasien;
   int maxPerRoom;
} Denah;

extern Denah denah;

/* I.S. denah belum terdefinisi
   F.S. denah terdefinisi dari file config.txt*/
void CreateDenah(Denah *denah, const char* folder);

/* I.S. denah sudah terdefinisi
   F.S. denah rumah sakit tercetak*/
void PrintDenah(Denah denah);

/* I.S. ruang dan denah sudah terdefinisi
   F.S. kapasitas pasien tercetak
        dokter di ruangan tercetak
        pasien-pasien di ruangan tercetak*/
void PrintRuang(Denah denah, char* ruang, int diluar);

/* I.S. denah sudah terdefinisi
   F.S. rows dan cols denah diubah sesuai dengan luas
        (jika rows atau cols lebih kecil dari awalnya, mengecek jika semua ruangan
         yang akan dikurangkan tidak ada orangnya) */
void UbahDenah(int newRow,int newCol);

#endif