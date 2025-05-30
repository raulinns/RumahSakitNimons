#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/ngobatin.h"

void NGOBATIN(User currentUser, ListRuangan ruangList, UserList* userList, ObatPenyakitList* obatPenyakitList)
{
    if (strcmp(currentUser.field[3], "Dokter") != 0) {
        printf("Anda tidak memiliki izin untuk memberikan obat.\n");
        return;
    }

    int idxRuangan = -1;
    for (int i = 0; i < MAX_USER; i++) {
        if (ruangList.ruangan[i].idDokter == atoi(currentUser.field[0]))
        {
            idxRuangan = i;
            break;
        }
    }

    if (idxRuangan == -1)
    {
        printf("Dokter belum diassign ke ruangan manapun.\n");
        return;
    }

    Queue* q = &ruangList.ruangan[idxRuangan].antrean;
    if (queue_isEmpty(*q))
    {
        printf("Tidak ada pasien di ruangan Anda.\n");
        return;
    }

    int idPasien = queue_front(q)->data;
    int idxPasien = -1;
    for (int i = 0; i < userList->len; i++)
    {
        if (atoi(userList->contents[i].field[0]) == idPasien)
        {
            idxPasien = i;
            break;
        }
    }

    if (idxPasien == -1)
    {
        printf("Pasien tidak ditemukan.\n");
        return;
    }

    User* pasien = &userList->contents[idxPasien];
    char* penyakit = pasien->field[6];
    if (strcmp(penyakit, "-") == 0 || strlen(penyakit) == 0)
    {
        printf("Pasien belum terdiagnosis penyakit.\n");
        return;
    }

    int idObat = -1;
    for (int i = 0; i < obatPenyakitList->len; i++)
    {
        if (strcmp(obatPenyakitList->contents[i].field[0], penyakit) == 0) {
            idObat = atoi(obatPenyakitList->contents[i].field[1]);
            break;
        }
    }

    if (idObat == -1)
    {
        printf("Tidak ditemukan obat untuk penyakit %s.\n", penyakit);
        return;
    }
    int idDokter = atoi(currentUser.field[0]);
    User* dokter = NULL;
    for (int i = 0; i < userList->len; i++)
    {
        if (atoi(userList->contents[i].field[0]) == idDokter)
        {
            dokter = &userList->contents[i];
            break;
        }
    }

    if (dokter == NULL)
    {
        printf("Data dokter tidak ditemukan.\n");
        return;
    }
    linked_delete(&dokter->inventoryObat, idObat);
    linked_insertEnd(&pasien->inventoryObat, idObat);
    printf("Obat berhasil diberikan kepada pasien %s.\n", pasien->field[1]);
}
