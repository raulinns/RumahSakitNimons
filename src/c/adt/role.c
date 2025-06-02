#include "../header/role.h"
#include "../header/file-utilities.h"
#include "../header/denah.h"
#include "../header/random.h"
#include <stdio.h>

DokterList dokterList;
PasienList pasienList;
ManagerList managerList;

int userPosByID(int id){
    for(int i = 0; i <= Ulist.len ; i++){
        if( atoi(Ulist.contents[i].field[0]) == id ) return i;
    }
    return -1;
}

/* MODUL SPESIFIK UNTUK PASIEN */

int UserID_to_PasienID(int id){
    for(int i = 0 ; i < pasienList.neff ; i++){
        if( PASIEN(i).id == id ) return i;
    }
    return -1;
}

void AddPasienList(int id){
    int neff = pasienList.neff;
    PASIEN(neff).id = id;
    PASIEN(neff).idDokter = -1; // Dokter belum di-assign
    if( strlen(Ulist.contents[userPosByID(id)].field[4]) > 0 ) PASIEN(neff).sudahDiagnosis = 1;
    else PASIEN(neff).sudahDiagnosis = 0;
    PASIEN(UserID_to_PasienID(id)).sudahDiobati = 0;
    pasienList.neff = pasienList.neff + 1;
}

void CekAntrian(int id){
    int userId = UserID_to_PasienID(id);

    if( PASIEN(userId).idDokter == -1 ) {
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        return;
    }

    int sz = 0;
    int pos = -1;
    Node* tempq = DOKTER(PASIEN(userId).idDokter).antrian->front;
    while( tempq != NULL ){
        if( tempq->data == id ) pos = sz;
        sz++;
        tempq = tempq->next;
    }
    if( pos < denah.maxPerRoom ){
        printf("\nAnda sedang berada di dalam ruangan dokter!\n");
    }

    else{
        int idDokter = PASIEN(userId).idDokter;
        printf("\nStatus antrian Anda:\n");
        printf("Dokter: Dr. %s\n", username(USER(Ulist,userPosByID(DOKTER(idDokter).id))));
        printf("Ruangan: %s\n", DOKTER(idDokter).ruangKerja);
        printf("Posisi antrian: %d dari %d\n", pos+1-denah.maxPerRoom, sz-denah.maxPerRoom);
    }
}

void DaftarCheckup(){
    if( PASIEN(UserID_to_PasienID(masterID)).idDokter != -1 ) {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    printf("\nSilakan masukkan data check-up Anda: \n");
    
    User* user = &USER(Ulist,userPosByID(masterID));
    
    printf("Suhu Tubuh (Celcius): ");
    scanf("%s", suhu(*user));
    while( atof(suhu(*user)) < 0 ){
        printf("Suhu tubuh harus berupa angka positif!\n");
        printf("Suhu Tubuh (Celcius): ");
        scanf("%s", suhu(*user));
    }

    printf("Tekanan Darah (sistol/diastol, contoh 120 8): ");
    scanf("%s %s", sistol(*user), diastol(*user));
    while( atoi(sistol(*user)) < 0 || atoi(diastol(*user)) < 0 ){
        printf("Tekanan darah harus berupa angka positif!\n");
        printf("Tekanan Darah (sistol/diastol, contoh 120 8): ");
        scanf("%s %s", sistol(*user), diastol(*user));
    }

    printf("Detak Jantung (bpm): ");
    scanf("%s", detak(*user));
    while( atoi(detak(*user)) < 0 ){
        printf("Detak Jantung harus berupa angka positif!\n");
        printf("Detak Jantung (bpm): ");
        scanf("%s", detak(*user));
    }

    printf("Saturasi Oksigen (%%): ");
    scanf("%s", saturasi(*user));
    while( atof(saturasi(*user)) < 0 || atof(saturasi(*user)) > 100 ){
        printf("Saturasi oksigen harus berada dalam rentang 0 sampai 100!\n");
        printf("Saturasi Oksigen (%%): ");
        scanf("%s", saturasi(*user));
    }

    printf("Kadar Gula Darah (mg/dL): ");
    scanf("%s", gula(*user));
    while( atoi(gula(*user)) < 0){
        printf("Kadar gula darah harus berupa angka positif!\n");
        printf("Kadar Gula Darah (mg/dL): ");
        scanf("%s", gula(*user));
    }

    printf("Berat Badan (kg): ");
    scanf("%s", berat(*user));
    while( atof(berat(*user)) <= 0){
        printf("Berat badan harus berupa angka positif!\n");
        printf("Berat Badan (kg): ");
        scanf("%s", berat(*user));
    }

    printf("Tinggi Badan (cm): ");
    scanf("%s", tinggi(*user));
    while( atoi(tinggi(*user)) <= 0){
        printf("Tinggi badan harus berupa angka positif!\n");
        printf("Tinggi Badan (cm): ");
        scanf("%s", tinggi(*user));
    }

    printf("Kadar Kolestrol (mg/dL): ");
    scanf("%s", kolesterol(*user));
    while( atoi(kolesterol(*user)) < 0){
        printf("Kolesterol badan harus berupa angka positif!\n");
        printf("Kolesterol Badan (mg/dL): ");
        scanf("%s", kolesterol(*user));
    }

    printf("Trombosit (ribu/µL): ");
    scanf("%s", trombosit(*user));
    while( atoi(trombosit(*user)) < 0){
        printf("Trombosit harus berupa angka positif!\n");
        printf("Trombosit (ribu/µL): ");
        scanf("%s", trombosit(*user));
    }

    // Print list dokter
    int cnt = 0; int temp[MAX_USER];
    for(int i = 0 ; i < dokterList.neff ; i++){
        if( strcmp(DOKTER(i).ruangKerja,"..") != 0 ){
            temp[cnt] = i;
            cnt++;
            printf("%d. Dr. %s - Spesialisasi %s - Ruangan %s (Antrian: %d orang) - Aura %d - Biaya %d\n", 
                cnt, username(USER(Ulist,userPosByID(DOKTER(i).id))), DOKTER(i).spesialisasi, DOKTER(i).ruangKerja, DOKTER(i).queue_size, DOKTER(i).aura, (DOKTER(i).aura+1)*120);
        }
    }

    if( dokterList.neff == 0 ){
        printf("Tidak ada dokter yang dapat dipilih!\n");
        return;
    }

    else {
        int pick;
        printf("\nPilih dokter (1-%d): ", cnt);
        scanf("%d", &pick);
        while( pick <= 0 || pick > cnt ){
            printf("Pilihan tidak valid!\n");
            printf("\nPilih dokter (1-%d): ", cnt);
            scanf("%d", &pick);
        }

        if( banarich[userPosByID(masterID)] < 120*(DOKTER(temp[pick-1]).aura+1) ){
            printf("Maaf Banarich kamu tidak cukup!\n");
            printf("Silakan pilih dokter lain atau mainkan mesin gacha!\n");
            return;
        }

        banarich[userPosByID(masterID)] -= 120*(DOKTER(temp[pick-1]).aura+1);
        banarich[userPosByID(DOKTER(temp[pick-1]).id)] += 96*(DOKTER(temp[pick-1]).aura+1);

        UpdateKasRumahSakit(24*(DOKTER(temp[pick-1]).aura+1));

        printf("\nPendaftaran check-up berhasil!\n");
        AddPasien_to_Dokter(masterID, DOKTER(temp[pick-1]).id);
        printf("Anda terdaftar pada antrian Dr. %s di ruangan %s.\n", username(USER(Ulist,userPosByID(DOKTER(temp[pick-1]).id))), DOKTER(temp[pick-1]).ruangKerja);
        printf("Posisi antrian Anda: %d\n", DOKTER(temp[pick-1]).queue_size);
    }
}

/* MODUL SPESIFIK UNTUK DOKTER */

void AddPasien_to_Dokter(int idPasien,int idDokter){
    int pos = UserID_to_DokterID(idDokter);
    int _idPasien = UserID_to_PasienID(idPasien);
    PASIEN(_idPasien).idDokter = pos;
    // Tambahkan pasien
    queue_push(DOKTER(pos).antrian, idPasien);
    DOKTER(pos).queue_size++;
}

/* Mengembalikan indeks dokter dengan nama sesuai parameter pada
   dokterList.
*/

int UserID_to_DokterID(int id){
    int l = 0, r = dokterList.neff-1;
    while(l <= r){
        int m = (l+r)/2;
        if( DOKTER(m).id == id ) return m;
        else if( DOKTER(m).id < id ) l = m+1;
        else r = m-1;
    }
    return -1;
}

int DokterList_NametoID(char* name){
    for(int i = 0 ; i < dokterList.neff ; i++){
        if( strcmp(name,username(USER(Ulist,userPosByID(DOKTER(i).id)))) == 0 ){
            return i;
        }
    }
    return -1;
}

void AddDokterList(int id){
    int neff = dokterList.neff;
    DOKTER(neff).id = id;
    strcpy(DOKTER(neff).ruangKerja,".."); // Ruang kerja belum di assign
    strcpy(DOKTER(neff).spesialisasi,"Umum");
    DOKTER(neff).antrian = malloc(sizeof(Queue));
    DOKTER(neff).aura = 0;
    queue_create(DOKTER(neff).antrian); //Order bug
    DOKTER(neff).queue_size = 0;
    dokterList.neff = dokterList.neff + 1;
}

void AssignDokter(){
    char stream[MAX_LINE_LENGTH];
    char ruang[3];
    printf("Username: ");
    scanf("%s", stream);
    printf("Ruangan: "); //TODO: cek apakah ruangan valid ASUMSI len maks 2
    scanf("%s", ruang);
    int getID = DokterList_NametoID(stream);

    // Temporary variables untuk pengecekan
    Map tMap = map_findMap(RuangtoDokter, ruang);
    char tRuang[3]; strcpy(tRuang, DOKTER(getID).ruangKerja);

    // Output berdasarkan kondisi dokter dan ruang yang ingin di assign
    if( getID == -1 ){ // Tidak terdapat dokter dengan nama yang sesuai
        printf("Tidak ada dokter dengan nama %s!\n", stream);
        return;
    }
    else if( strcmp(tRuang,"..") != 0 && tMap == NULL  ){ // Dokter sudah di assign dan ruang kosong
        printf("Dokter %s sudah diassign ke ruangan %s!\n", stream, DOKTER(getID).ruangKerja);
    }
    else if(  strcmp(tRuang,"..") == 0 && tMap != NULL ){     // Dokter belum di assign tetapi ruangan sudah diisi oleh dokter lain
        printf("Dokter %s sudah menempati ruangan %s!\n", username(USER(Ulist,userPosByID(tMap->value))),ruang);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", stream);
    }
    else if( strcmp(tRuang,"..") != 0 && tMap != NULL) { // Dokter sudah di assign dan ruangan juga sudah ditempati
        printf("Dokter %s sudah menempati ruangan %s!\n", stream, tRuang);
        printf("Ruangan %s juga sudah ditempati dokter %s!\n", ruang, username(USER(Ulist,userPosByID(tMap->value))));
    }
    else{
        map_insert(&RuangtoDokter, ruang, DOKTER(getID).id);
        strcpy(DOKTER(getID).ruangKerja,ruang);
        printf("\nDokter %s berhasil diassign ke ruangan %s!\n", stream, ruang);
        denah.M.contents[ruang[0]-'A'][ruang[1]-'1'] = DOKTER(getID).id;
    }
}

/* MODUL SPESIFIK UNTUK MANAGER */
void AddManagerList(int id){
    int neff = managerList.neff;
    MANAGER(neff).id = id;
    managerList.neff = managerList.neff + 1;
}