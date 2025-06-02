#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <stdlib.h>
#include <string.h>
#include "file/ext-list.h"
#include "adt/list.h"
#include "adt/map.h"
#include "adt/set.h"
#include "denah.h"

extern Map RuangtoDokter;
/* Mengembalikan path yang diinginkan:
        ../file/dir/name
*/
void path(char* dest, const char* dir, const char* name);

/* Melakukan parsing line dari setiap file external */
//void parser(char* line,fields* field);

// Membuat path lengkap file dari folder dan nama file
void path(char* dest, const char* dir, const char* name);

// Mengecek apakah folder/file ada dengan mencoba membuka file
int folder_exists(const char* path);

/* Menghitung jumlah field dalam satu baris data yang dipisah oleh token
   dan menyimpan hasil parsing dalam array field.
*/
int parser(char* line, fields* field, char token);

// Memuat semua data yang diperlukan dari folder ke struktur data yang sesuai
int load_all(char* folder, Denah* denah, UserList* Ulist,
             ObatList* Olist, ObatPenyakitList* OPlist, PenyakitList* Plist);

// Memuat konfigurasi denah dan pengguna dari file config.txt dalam folder
int load_config(char* folder, Denah* denah, UserList* Ulist);

// Memuat data obat dari file obat.csv dalam folder
int load_obat(char* folder, ObatList* l);

// Memuat data penyakit dari file penyakit.csv dalam folder
int load_penyakit(char* folder, PenyakitList* l);

// Memuat data user dari file user.csv dalam folder
int load_user(char* folder, UserList* l);

// Memuat data hubungan obat dan penyakit dari file obat-penyakit.csv
int load_obatpenyakit(char* folder, ObatPenyakitList* l);

// Memuat data banarich dari file banarich.csv, atau inisialisasi jika file tidak ada
int load_banarich(char* folder);

// Menambahkan user baru ke daftar dan set jika username belum ada
void add_user(List *Ulist, Set* Uset);

// Menyimpan data user ke file user.csv pada folder yang sudah ditentukan
int save_user(UserList* l);

// Menyimpan data penyakit ke file penyakit.csv pada folder yang sudah ditentukan
int save_penyakit(PenyakitList* l);

// Menyimpan data obat ke file obat.csv pada folder yang sudah ditentukan
int save_obat(ObatList* l);

// Menyimpan data hubungan obat-penyakit ke file obat-penyakit.csv
int save_obatpenyakit(ObatPenyakitList* l);

// Menyimpan data banarich ke file banarich.csv pada folder yang sudah ditentukan
void save_banarich(void);

// Menyimpan seluruh data ke dalam folder yang ditentukan,
// membuat folder jika belum ada
int save_all(char* folderName, ObatList* obatList, ObatPenyakitList* obatPenyakitList,
             PenyakitList* penyakitList, UserList* userList);


#endif