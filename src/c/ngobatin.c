#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/role.h"
#include "../header/ngobatin.h"

void NGOBATIN(User currentUser, ListRuangan ruangList, UserList* userList, ObatPenyakitList* obatPenyakitList)
{
    if (strcmp(currentUser.field[3], "dokter") != 0) {
        printf("Anda tidak memiliki izin untuk memberikan obat.\n");
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
        printf("Tidak ada pasien di ruangan Anda.\n");
        return;
    }

    // TODO : cek apakah queue harus di pop atau tidak

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

    User* pasien = &userList->contents[idxPasien]; // TODO : fix config
    
    char* penyakit = pasien->field[4];
    int idPenyakit = -1;
    for(int i = 0; i < Plist.len ; i++){
        if( strcmp(Plist.contents[i].field[1], penyakit) == 0 ) idPenyakit = atoi(Plist.contents[i].field[0]);
    }
    
    if( idPenyakit == - 1){
        printf("Penyakit tidak ditemukan!\n");
        return;
    }

    if (strcmp(penyakit, "-") == 0 || strlen(penyakit) == 0)
    {
        printf("Pasien tidak memiliki penyakit.\n");
        return;
    }

    if( PASIEN(UserID_to_PasienID(atoi(pasien->field[0]))).sudahDiagnosis == 0 ){
        printf("Pasien belum di diagnosis!\n");
        return;
    }

    int idObat = -1;
    int obatPenyakit[MAX_USER];
    int _len = 0;
    printf("id penyakit : %d\n", idPenyakit);
    for (int i = 0; i < obatPenyakitList->len; i++)
    {
        if ( atoi(obatPenyakitList->contents[i].field[1]) == idPenyakit) {
            idObat = atoi(obatPenyakitList->contents[i].field[0]);
            obatPenyakit[atoi(obatPenyakitList->contents[i].field[2])] = idObat;
            _len++;
        }
    }

    printf("Pasien memiliki penyakit %s\n", penyakit);
    printf("Obat yang harus diberikan:\n");
    for(int i = 0; i < _len ; i++){ // O(N^2) gapapa lah ya
        for(int j = 0; j < Olist.len ; j++){
            if( atoi(Olist.contents[j].field[0]) == obatPenyakit[i+1]  ){
                printf("%d. %s\n", i+1, Olist.contents[j].field[1]);
            }
        }
    }
}
