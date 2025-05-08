#ifndef DENAH_H
#define DENAH_H

#include "../header/adt/matrix.h"
#include "../header/user.h"

char *ParseData(char *line, int *i, char token);

/* I.S. denah belum terdefinisi
   F.S. denah terdefinisi dari file config.txt*/
void CreateDenah(Matrix *denah);

/* I.S. denah sudah terdefinisi
   F.S. denah rumah sakit tercetak*/
void PrintDenah(Matrix denah);

/* I.S. ruang dan denah sudah terdefinisi
   F.S. kapasitas pasien tercetak
        dokter di ruangan tercetak
        pasien-pasien di ruangan tercetak*/
void PrintRuang(char *ruang, Matrix denah);

/* I.S. denah sudah terdefinisi
   F.S. rows dan cols denah diubah sesuai dengan luas
        (jika rows atau cols lebih kecil dari awalnya, mengecek jika semua ruangan
         yang akan dikurangkan tidak ada orangnya) */
void UbahDenah(char *luas, Matrix *denah);

#endif