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

/* Menyimpan seluruh data ke struktur data masing-masing*/
int load_all(char* folder, Denah* denah, UserList* Ulist,
             ObatList* Olist, ObatPenyakitList* OPlist, PenyakitList* Plist);

/* Menyimpan data dari obat.csv ke ObatList*/
int load_obat(char* folder,ObatList* l);

/* Menyimpan data dari penyakit.csv ke PenyakitList*/
int load_penyakit(char* folder,PenyakitList* l);

/* Menyimpan data dari user.csv ke UserList*/
int load_user(char* folder,UserList* l);

/* Menyimpan data dari obat-penyakit.csv*/
int load_obatpenyakit(char* folder, ObatPenyakitList* l);

/* Menambahkan user baru ke variabel interal (list dan set)*/
void add_user(List *Ulist,Set* Uset);

int save_user(UserList* l);

int save_penyakit(PenyakitList* l);

int save_obat(ObatList* l);

int save_obatpenyakit(ObatPenyakitList* l);

int save_all(char* folderName,ObatList* obatList,ObatPenyakitList* obatPenyakitList,
            PenyakitList* penyakitList,UserList* userList);

#endif