#ifndef PULANG_H
#define PULANG_H

#include "../header/file/user.h"
#include "../header/file/obat-penyakit.h"
#include "../header/file/obat.h"

/* Mengembalikan 1 jika pasien boleh pulang (sebagai tambahan untuk B03 Aura)*/
int pulangdok(User Pasien, ObatPenyakitList OPlist, ObatList Olist);

#endif