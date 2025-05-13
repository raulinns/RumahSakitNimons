#ifndef EXTFILE_H
#define EXTFILE_H

#include "file-utilities.h"

int load(char* folder, UserList* listUser, PenyakitList* listPenyakit,
         ObatList* listObat, ObatPenyakitList* listObatPenyakit)
{
    /*  Cek apakah folder ada */
    // if( load_config)
    /* Load seluruh data dari filde ../data/folder */
    load_user(folder,listUser);
    load_penyakit(folder,listPenyakit);
    load_obat(folder,listObat);
    load_obatpenyakit(folder,listObatPenyakit);

}

#endif