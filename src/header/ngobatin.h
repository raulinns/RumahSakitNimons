#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "user.h"
#include "hospital.h"
#include "adt/linkedlist.h"
#include "file/penyakit.h"
#include "adt/queue.h"
#include "file-utilities.h"

/*
Dokter memberikan obat kepada pasien sesuai penyakit yang sudah didiagnosis.
Obat hanya diberikan jika dokter memiliki obat yang sesuai dengan penyakit.
Obat akan dipindahkan dari inventory dokter ke inventory pasien.
currentUser: dokter yang sedang login
ruangList: List seluruh ruangan
userList: List semua user (dokter dan pasien)
obatPenyakitList: List relasi penyakit dan obat dari obat-penyakit.csv
*/
void NGOBATIN(User currentUser, ListRuangan ruangList, UserList* userList, ObatPenyakitList* obatPenyakitList);

#endif