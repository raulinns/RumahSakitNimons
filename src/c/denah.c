#include "../header/user.h"
#include "../header/file-utilities.h"
#include "../header/file/ext-list.h"
#include "../header/denah.h"
#include "../header/role.h"
#include "../header/adt/queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Denah denah;

void CreateDenah(Denah *denah, const char* folder) {
    // Build path to config.txt: "data/folder/config.txt"
    char path[256];
    snprintf(path, sizeof(path), "data/%s/config.txt", folder);
    
    FILE *configFile = fopen(path, "r");
    if (!configFile) {
        perror("Gagal membuka config.txt");
        exit(1);
    }
    
    char line[MAX_LINE_LENGTH];
    
    // First line: rows and cols
    if (!fgets(line, MAX_LINE_LENGTH, configFile)) {
        fprintf(stderr, "Error reading first line\n");
        fclose(configFile);
        exit(1);
    }
    
    int rowIdx = 0;
    char *rowStr = ParseData(line, &rowIdx, ' ');
    if (!rowStr) {
        fprintf(stderr, "Failed to parse rows\n");
        fclose(configFile);
        exit(1);
    }
    
    int rows = atoi(rowStr);
    free(rowStr); // DEALLOC
    
    char *colStr = ParseData(line, &rowIdx, ' ');
    if (!colStr) {
        fprintf(stderr, "Failed to parse cols\n");
        fclose(configFile);
        exit(1);
    }
    
    int cols = atoi(colStr);
    free(colStr); // DEALLOC
    
    ROWS(MAT(*denah)) = rows;
    COLS(MAT(*denah)) = cols;

    if (!fgets(line, MAX_LINE_LENGTH, configFile)) {
        fprintf(stderr, "Error reading second line\n");
        fclose(configFile);
        exit(1);
    }
    
    int maxIdx = 0;
    char *maxPasienStr = ParseData(line, &maxIdx, ' ');
    if (!maxPasienStr) {
        fprintf(stderr, "Failed to parse maxPasien\n");
        fclose(configFile);
        exit(1);
    }
    
    int maxPasien = atoi(maxPasienStr);
    free(maxPasienStr);
    denah->maxPasien = maxPasien;
    
    NEFF(LIST(*denah)) = maxPasien + maxPasien * cols + maxPasien * cols * rows;
    
    // Inisialisasi ruangan
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            CNTN(MAT(*denah), i, j) = 0; 
        }
    }
    
    fclose(configFile);
}


void PrintDenah(Denah denah) {
    int i, j;
    for (i = 0; i < COLS(MAT(denah)); i++) {
        printf("     %d", i + 1);
    }
    printf("\n   +");
    for (i = 0; i < COLS(MAT(denah)); i++) {
        printf("-----+");
    }
    printf("\n");
    for (i = 0; i < ROWS(MAT(denah)); i++) {
        printf(" %c |", (char)(i + 65));
        for (j = 0; j < COLS(MAT(denah)); j++) {
            printf(" %c%d  |", (char)(i + 65), j + 1);
        }
        printf("\n");
        printf("   +");
        for (j = 0; j < COLS(MAT(denah)); j++) {
            printf("-----+");
        }
        printf("\n");
    }
}

void PrintRuang(Denah denah, char* ruang, int diluar) {
    // Print heaeder
    if( diluar == 0 ){
        printf("\n--- Detail Ruangan %s ---\n", ruang);
        printf("Kapasitas  : %d\n", denah.maxPerRoom);     
    }
    else{
        printf("============ %s ============\n", ruang);
    }
    
    Map temp = map_findMap(RuangtoDokter, ruang);
    
    // Handle kasus kosong
    if( temp == NULL ){
        printf("Dokter     : - \n");
        printf("Pasien di dalam ruangan:\n");
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
        printf("Pasien di antrian:\n");
        printf("  Tidak ada pasien di antrian saat ini.\n");
        return;
    }

    // Print header
    
    printf("Dokter     : ");
    if ( temp != NULL ) {
        printf("Dr. %s\n", username(USER(Ulist,userPosByID(temp->value))));
    }
    else {
        printf(" -\n");
    }

    Node* tempq = DOKTER(UserID_to_DokterID(temp->value)).antrian->front;
    
    // Print queue
    int cur = 1;
    printf("Pasien di dalam ruangan:\n");
    if( tempq == NULL ) printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    else{
        while( tempq != NULL && cur <= denah.maxPerRoom ){
            printf(" %d. %s\n", cur, username(USER(Ulist,userPosByID(tempq->data))));
            cur++;
            tempq = tempq->next;
        }
    }
    printf("\n");

    // Print pasien yang diluar
    if( diluar == 0 ) return;
    printf("Pasien di antrian:\n");
    if( tempq == NULL ) printf("  Tidak ada pasien di antrian saat ini.\n");
    else{
        while( tempq != NULL ){
            printf(" %d. %s\n", cur, username(USER(Ulist,userPosByID(tempq->data))));
            cur++;
            tempq = tempq->next;
        }
    }
}

void UbahDenah(char *luas, Denah *denah) {
    int i = 0;
    ParseData(luas, &i, ' ');
    int rows = atoi(ParseData(luas, &i, ' '));
    int cols = atoi(ParseData(luas, &i, ' '));
    int valid = 1;
    if (ROWS(MAT(*denah)) > rows && COLS(MAT(*denah)) > cols) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (i >= rows && j >= cols && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    else if (ROWS(MAT(*denah)) > rows) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (i >= rows && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    else if (COLS(MAT(*denah)) > cols) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (j >= cols && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    if (valid) {
        ROWS(MAT(*denah)) = rows;
        COLS(MAT(*denah)) = cols;
        printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom\n", rows, cols);
    }
}

void SkipAntrian() {
    if (strcmp(role(USER(Ulist,userPosByID(masterID))), "pasien") != 0) {
        printf("Akses tidak dimiliki!\n");
        return;
    }

    int idDokter = PASIEN(UserID_to_PasienID(masterID)).idDokter;
    
    if( idDokter == -1 ){
        printf("Skip antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun!\n");
        return;
    }

    if( DOKTER(idDokter).antrian->front->data == masterID ){
        printf("Skip antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun!\n");
        return;
    }
    Queue* oldQueue = DOKTER(idDokter).antrian;
    Queue* newQueue = malloc(sizeof(Queue));
    queue_create(newQueue);

    // Tambah masterID di depan
    queue_push(newQueue, masterID);

    // Salin antrean lama, kecuali masterID
    Node* temp = oldQueue->front;
    while (temp != NULL) {
        if (temp->data != masterID) {
            queue_push(newQueue, temp->data);
        }
        temp = temp->next;
    }

    // Hapus antrean lama dan ganti dengan antrean baru
    queue_clear(oldQueue);
    free(oldQueue);  // Hindari memory leak
    DOKTER(idDokter).antrian = newQueue;
    printf("Anda berhasil maju ke depan antrian Dr. %s di ruangan %s!\n", username(USER(Ulist,userPosByID(DOKTER(idDokter).id))), DOKTER(idDokter).ruangKerja);
    printf("Posisi antrian Anda sekarang: 1\n");
}

void KeluarAntrian() {
    if (strcmp(role(USER(Ulist,userPosByID(masterID))), "pasien") != 0) {
        printf("Akses tidak dimiliki!\n");
        return;
    }

    int idDokter = PASIEN(UserID_to_PasienID(masterID)).idDokter;
    if( idDokter == -1 ) {
        printf("Pembatalan antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun!\n");
    }
    Queue* oldQueue = DOKTER(idDokter).antrian;
    Queue* newQueue = malloc(sizeof(Queue));
    queue_create(newQueue);

    Node* temp = oldQueue->front;
    while (temp != NULL) {
        if (temp->data != masterID) {
            queue_push(newQueue, temp->data);
        }
        temp = temp->next;
    }

    queue_clear(oldQueue);
    free(oldQueue);
    DOKTER(idDokter).antrian = newQueue;

    printf("Anda berhasil keluar dari antrian Dr. %s di ruangan %s.", username(USER(Ulist,userPosByID(DOKTER(idDokter).id))), DOKTER(idDokter).ruangKerja); 
}
