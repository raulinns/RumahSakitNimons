#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "user.h"
#include "hospital.h"
#include "adt/queue.h"

/*
Menjalankan proses diagnosis untuk pasien pertama di ruangan yang diassign ke dokter saat ini
currentUser: dokter yang sedang login
ruangList: ListRuangan
userList: UserList
penyakitList: daftar penyakit dari penyakit.csv
*/
void DIAGNOSIS(User currentUser, ListRuangan ruangList, UserList* userList, PenyakitList* penyakitList);

#endif
