#include "../header/pulang.h"
#include "../header/role.h"
#include <stdio.h>
#include <string.h>

int pulangdok() {
    printf("\n");
    
    User* Pasien;
    for (int i = 0; i != Ulist.len; i++) {
        if ( atoi(Ulist.contents[i].field[0]) == masterID ) {
            Pasien = &Ulist.contents[i];
            break;
        }
    }
    
    char* penyakit = riwayat(*Pasien);
    
    if( PASIEN(UserID_to_PasienID(atoi(Pasien->field[0]))).sudahDiagnosis == 0 ){
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
    }
    
    printf("Dokter sedang memeriksa keadaanmu...\n\n");
    
    if (strcmp(riwayat(*Pasien), "-") == 0 || strlen(riwayat(*Pasien)) == 0) {
        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
        return 1;
    }
    
    
    if (Pasien->inventoryObat.size != 0) {
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }
    
    int idx = 0;
    int idPenyakit = -1;

    for(int i = 0 ; i < Plist.len ; i++){
        if( strcmp(PENYAKIT(Plist,i).field[1],penyakit) == 0){
            idPenyakit = atoi(PENYAKIT(Plist,i).field[0]);
        }
    }
    
    ObatPenyakitList NewOPlist;
    NewOPlist.len = 0;
    for (int i = 0; i != OPlist.len; i++) {
        if (atoi(OPlist.contents[i].field[1]) == idPenyakit) {
            NewOPlist.contents[idx] = OPlist.contents[i];
            NewOPlist.len++; idx++;
        }
    }
    
    //Pindahkan id obat sesuai urutan
    int len = NewOPlist.len;
    int arr1[len];
    for (int i = 0; i != len; i++) {
        int j = 0;
        while (atoi(NewOPlist.contents[j].field[2]) != i + 1) {
            j++;
        }
        arr1[i] = atoi(NewOPlist.contents[j].field[0]);
    }

    Stack perut;
    perut = Pasien->perut;
    int arr2[len];
    for (int i = len - 1; i != -1; i--) {
        arr2[i] = perut.top->data;
        stack_pop(&perut);
    }
    int beda = 0;
    for (int i = 0; i != len && !beda; i++) {
        if (arr1[i] != arr2[i]) {
            beda = 1;
        }
    }

    if (beda) {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i != len; i++) {
            int j = 0;
            while ( atoi(Olist.contents[j].field[0]) != arr1[i]) {
                j++;
            }
            printf("%s", Olist.contents[j].field[1]);
            if (i != len - 1) {
                printf(" -> ");
            }
        }
        printf("\n\n");
        printf("Urutan obat yang kamu minum:\n");
        for (int i = 0; i != len; i++) {
            int j = 0;
            while ( atoi(Olist.contents[j].field[0]) != arr2[i]) {
                j++;
            }
            printf("%s", Olist.contents[j].field[1]);
            if (i != len - 1) {
                printf(" -> ");
            }
        }
        printf("\n\n");
        printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        return 0;
    }
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
    return 1;
}