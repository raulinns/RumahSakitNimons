#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/diagnosis.h"
#include "../header/role.h"

//TODO: Cek kondisi lain dari pasien
void DIAGNOSIS(User currentUser, ListRuangan ruangList, UserList *userList, PenyakitList *penyakitList)
{
    if (strcmp(currentUser.field[3], "dokter") != 0)
    {
        for(int i = 0 ; i < 5 ; i++) printf("%s\n", currentUser.field[i]);
        printf("Anda tidak memiliki izin untuk melakukan diagnosis.\n");
        return;
    }
    int idDokter = UserID_to_DokterID(masterID);
    if( strcmp(DOKTER(idDokter).ruangKerja,"..") == 0 ){
        printf("Dokter belum diassign ke ruangan manapun.\n");
        return;
    }

    Queue *q = DOKTER(idDokter).antrian;
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
            idxPasien = i; // ASUMSI: ID belom sesuai config
            break;
        }
    }

    if (idxPasien == -1)
    {
        printf("Data pasien tidak ditemukan.\n");
        return;
    }

    User *pasien = &userList->contents[idxPasien];
    float suhu = atof(pasien->field[5]);
    int sistolik = atoi(pasien->field[6]);

    int cocok = 0;
    for (int i = 1; i < penyakitList->len; i++)
    {
        float suhu_min = atof(penyakitList->contents[i].field[2]);
        float suhu_max = atof(penyakitList->contents[i].field[3]);
        int sis_min = atoi(penyakitList->contents[i].field[4]);
        int sis_max = atoi(penyakitList->contents[i].field[5]);
        printf("%f %d %f %f %d %d\n", suhu, sistolik, suhu_min, suhu_max, sis_min, sis_max);
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
