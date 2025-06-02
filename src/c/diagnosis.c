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

    if( strcmp(riwayat(*pasien),"-") != 0 && strlen(riwayat(*pasien)) > 0) {
        printf("Pasien sudah pernah didiagnosis penyakit %s!\n", riwayat(*pasien));
        printf("Silakan gunakan perintah 'NGOBATIN' untuk memberikan obat kepada pasien.\n");
        return;
    }

    PASIEN(UserID_to_PasienID(atoi(pasien->field[0]))).sudahDiagnosis = 1;

    float f_suhu       = atof(suhu(*pasien));
    int i_sistol       = atoi(sistol(*pasien));
    int i_diastol      = atoi(diastol(*pasien));
    int i_detak        = atoi(detak(*pasien));
    float f_saturasi   = atof(saturasi(*pasien));
    int i_gula         = atoi(gula(*pasien));
    float f_berat      = atof(berat(*pasien));
    int i_tinggi       = atoi(tinggi(*pasien));
    int i_kolesterol   = atoi(kolesterol(*pasien));
    int i_trombosit    = atoi(trombosit(*pasien));

    int ditemukan = 0;
    for (int i = 0; i < penyakitList->len; i++)
    {
        Penyakit penyakit = penyakitList->contents[i];
        if (
            f_suhu       >= atof(suhu_min(penyakit))       && f_suhu      <= atof(suhu_max(penyakit))        &&
            i_sistol     >= atoi(sistol_min(penyakit))     && i_sistol    <= atoi(sistol_max(penyakit))      &&
            i_diastol    >= atoi(diastol_min(penyakit))    && i_diastol   <= atoi(diastol_max(penyakit))     &&
            i_detak      >= atoi(detak_min(penyakit))      && i_detak     <= atoi(detak_max(penyakit))       &&
            f_saturasi   >= atof(saturasi_min(penyakit))   && f_saturasi  <= atof(saturasi_max(penyakit))    &&
            i_gula       >= atoi(gula_min(penyakit))       && i_gula      <= atoi(gula_max(penyakit))        &&
            f_berat      >= atof(berat_min(penyakit))      && f_berat     <= atof(berat_max(penyakit))       &&
            i_tinggi     >= atoi(tinggi_min(penyakit))     && i_tinggi    <= atoi(tinggi_max(penyakit))      &&
            i_kolesterol >= atoi(kolesterol_min(penyakit)) && i_kolesterol <= atoi(kolesterol_max(penyakit)) &&
            i_trombosit  >= atoi(trombosit_min(penyakit))  && i_trombosit <= atoi(trombosit_max(penyakit))
        )
        {
            strcpy(riwayat(*pasien), penyakit(penyakit));
            printf("%s terdiagnosa penyakit %s!\n", username(*pasien), riwayat(*pasien));
            ditemukan = 1;
            break;
        }
    }

    if (!ditemukan)
    {
        strcpy(riwayat(*pasien), "-");
        printf("%s tidak terdiagnosis penyakit apapun!\n", username(*pasien));
    }
}
