#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/minum-obat.h"
#include "../header/role.h"

void minumObat(){
    //Print daftar obat di inventory pasien nyimpen id obat
    User* pasien;
    for(int i = 0 ; i < Ulist.len ; i++){
        if( atoi(Ulist.contents[i].field[0]) == masterID ) {pasien = &Ulist.contents[i]; break;}
    }
    
    printf("========== DAFTAR OBAT ==========\n");
    printf("0. Keluar\n");
    Node* current = pasien->inventoryObat.head;
    List* tempNamaObat = malloc(sizeof(List));
    List* tempIdObat = malloc(sizeof(List));
    list_create(tempNamaObat);
    list_create(tempIdObat);
    int nomor = 1;
    while(current != NULL){
        int id_obat = current->data;
        for(int i=0; i<Olist.len; i++){
            if (id_obat == atoi(Olist.contents[i].field[0])){
                printf("%d. %s\n", nomor, Olist.contents[i].field[1]);

                char id_obat_str[CAPACITY];
                sprintf(id_obat_str, "%d", id_obat);
                list_add(tempIdObat, id_obat_str);                      //simpan id obat
                list_add(tempNamaObat, Olist.contents[i].field[1]); //simpen nama obat
                nomor++;
                break;
            }
        }
        current = current->next;
    }

    int no_obat_hapus;
    do {
        printf("Pilih obat untuk diminum (masukkan 0 untuk keluar): ");
        scanf("%d", &no_obat_hapus);
        if (no_obat_hapus == 0) {
            printf("Tidak jadi minum obat.\n");
            free(tempIdObat);
            free(tempNamaObat);
            return;
        }
    } while (no_obat_hapus < 1 || no_obat_hapus >= nomor);
    
    printf("GLEKGLEKGLEK...%s berhasil diminum!!\n", tempNamaObat->contents[no_obat_hapus-1]);

    //Hapus id obat dari inventory pasien
    int id_obat_hapus = atoi(tempIdObat->contents[no_obat_hapus-1]);
    //Cari indeks node yang menyimpan id_obat_hapus
    int index = 0;
    current = pasien->inventoryObat.head;
    while (current != NULL) {
        if (current->data == id_obat_hapus) {
            break;
        }
        current = current->next;
        index++;
    }
    linked_delete(&pasien->inventoryObat, index);
    tempIdObat->nEff = 0;
    tempNamaObat->nEff = 0;
    free(tempIdObat);
    free(tempNamaObat);

    //Masukkin id_obat yang diminum ke perut pasien
    stack_push(&pasien->perut, id_obat_hapus);
}

void minumPenawar(){
    User* pasien;
    for(int i = 0 ; i < Ulist.len ; i++){
        if( atoi(Ulist.contents[i].field[0]) == masterID ) {pasien = &Ulist.contents[i]; break;}
    }

    if (stack_isEmpty(pasien->perut)){
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
    } else{
        //Keluarin id_obat yang dimuntahin dr perut pasien
        char* nama_obat = NULL;
        int id_obat = stack_top(&pasien->perut.top);
        for(int i=0; i<Olist.len; i++){
            if (id_obat == atoi(Olist.contents[i].field[0])){
                nama_obat = Olist.contents[i].field[1];
                break;
            }
        }
        if (nama_obat != NULL){
            printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", nama_obat);
            stack_pop(&pasien->perut);
        }

        //Tambahkan lagi ke inventory
        linked_insertEnd(&pasien->inventoryObat, id_obat);     
    }
}