#include "../header/pulang.h"
#include "../header/role.h"
#include <stdio.h>
#include <string.h>

int pulangdok() {
    printf("\n");
    
    User* Pasien = NULL;
    for (int i = 0; i < Ulist.len; i++) {
        if (atoi(Ulist.contents[i].field[0]) == masterID) {
            Pasien = &Ulist.contents[i];
            break;
        }
    }
    
    if (Pasien == NULL) {
        printf("Error: User tidak ditemukan.\n");
        return 0;
    }
    
    char* penyakit = riwayat(*Pasien);
    
    if (PASIEN(UserID_to_PasienID(atoi(Pasien->field[0]))).sudahDiagnosis == 0) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return 0;
    }
    
    printf("Dokter sedang memeriksa keadaanmu...\n\n");
    
    if (strcmp(riwayat(*Pasien), "-") == 0 || strlen(riwayat(*Pasien)) == 0) {
        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
        return 1;
    }
    
    if (Pasien->inventoryObat.size != 0) {
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return 0;
    }
    
    int idPenyakit = -1;
    for (int i = 0; i < Plist.len; i++) {
        if (strcmp(PENYAKIT(Plist,i).field[1], penyakit) == 0) {
            idPenyakit = atoi(PENYAKIT(Plist,i).field[0]);
            break;
        }
    }
    
    ObatPenyakitList NewOPlist;
    NewOPlist.len = 0;
    for (int i = 0; i < OPlist.len; i++) {
        if (atoi(OPlist.contents[i].field[1]) == idPenyakit) {
            NewOPlist.contents[NewOPlist.len] = OPlist.contents[i];
            NewOPlist.len++;
        }
    }
    
    int len = NewOPlist.len;
    int arr1[len];
    for (int i = 0; i < len; i++) {
        int j = 0;
        int found = 0;
        while (j < NewOPlist.len) {
            if (atoi(NewOPlist.contents[j].field[2]) == i + 1) {
                arr1[i] = atoi(NewOPlist.contents[j].field[0]);
                break;
            }
            j++;
        }
    }

    // Check if stack has enough elements
    Stack perutCopy = Pasien->perut;
    
    int arr2[len];
    for (int i = len - 1; i >= 0; i--) {
        arr2[i] = perutCopy.top->data;
        stack_pop(&perutCopy);
    }
    
    int beda = 0;
    for (int i = 0; i < len && !beda; i++) {
        if (arr1[i] != arr2[i]) {
            beda = 1;
        }
    }

    if (beda) {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < len; i++) {
            int j = 0;
            int found = 0;
            while (j < Olist.len) {
                if (atoi(Olist.contents[j].field[0]) == arr1[i]) {
                    found = 1;
                    break;
                }
                j++;
            }
            if (!found) {
                printf("[Obat tidak ditemukan]");
            } else {
                printf("%s", Olist.contents[j].field[1]);
            }
            if (i != len - 1) {
                printf(" -> ");
            }
        }
        printf("\n\n");
        printf("Urutan obat yang kamu minum:\n");
        for (int i = 0; i < len; i++) {
            int j = 0;
            int found = 0;
            while (j < Olist.len) {
                if (atoi(Olist.contents[j].field[0]) == arr2[i]) {
                    found = 1;
                    break;
                }
                j++;
            }
            if (!found) {
                printf("[Obat tidak ditemukan]");
            } else {
                printf("%s", Olist.contents[j].field[1]);
            }
            if (i != len - 1) {
                printf(" -> ");
            }
        }
        printf("\n\n");
        printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        return 0;
    }

    int idDokter = PASIEN(UserID_to_PasienID(atoi(Pasien->field[0]))).idDokter;
    if (DOKTER(idDokter).antrian->size > 0) {
        queue_pop(DOKTER(idDokter).antrian);
    }
    DOKTER(idDokter).aura++;
    PASIEN(UserID_to_PasienID(atoi(Pasien->field[0]))).idDokter = -1;
    
    // Reset data user.csv
    for (int i = 4; i < 16; i++) {
        strcpy(Pasien->field[i], "");
    }

    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
    return 1;
}