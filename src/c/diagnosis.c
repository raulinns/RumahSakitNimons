#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/diagnosis.h"

void DIAGNOSIS(User currentUser, ListRuangan ruangList, UserList *userList, PenyakitList *penyakitList)
{
    if (strcmp(currentUser.field[3], "Dokter") != 0)
    {
        printf("Anda tidak memiliki izin untuk melakukan diagnosis.\n");
        return;
    }
    int idxRuangan = -1;
    for (int i = 0; i < MAX_USER; i++)
    {
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

    Queue *q = &ruangList.ruangan[idxRuangan].antrean;
    if (queue_isEmpty(*q))
    {
        printf("Tidak ada pasien untuk diperiksa!\n");
        return;
    }

    int idPasien = queue_front(q)->data;
    queue_pop(q);

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
        printf("Data pasien tidak ditemukan.\n");
        return;
    }

    User *pasien = &userList->contents[idxPasien];
    float suhu = atof(pasien->field[4]);
    int sistolik = atoi(pasien->field[5]);

    int cocok = 0;
    for (int i = 0; i < penyakitList->len; i++)
    {
        float suhu_min = atof(penyakitList->contents[i].field[2]);
        float suhu_max = atof(penyakitList->contents[i].field[3]);
        int sis_min = atoi(penyakitList->contents[i].field[4]);
        int sis_max = atoi(penyakitList->contents[i].field[5]);

        if (suhu >= suhu_min && suhu <= suhu_max &&
            sistolik >= sis_min && sistolik <= sis_max)
            {
            strcpy(pasien->field[6], penyakitList->contents[i].field[1]);
            printf("%s terdiagnosa penyakit %s!\n", pasien->field[1], pasien->field[6]);
            cocok = 1;
            break;
        }
    }

    if (!cocok)
    {
        strcpy(pasien->field[6], "-");
        printf("%s tidak terdiagnosis penyakit apapun!\n", pasien->field[1]);
    }
}
