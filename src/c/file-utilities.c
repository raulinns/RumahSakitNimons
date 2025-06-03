#include "../header/adt/map.h"
#include "../header/file-utilities.h"
#include "../header/denah.h"
#include "../header/user.h"
#include "../header/role.h"
#include "../header/adt/map.h"
#include "../header/file/ext-list.h"
#include "../header/login.h"
#include <string.h>

Map RuangtoDokter;

void path(char* dest, const char* dir, const char* name){
    strcpy(dest, "data/");
    strcat(dest, dir);
    strcat(dest, "/");
    strcat(dest, name);
}

int folder_exists(const char* path) {
    FILE* fp = fopen(path, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1; // Ada
    }
    return 0; // Tidak ada
}

/*  Mengembalikan jumlah field yang terdapat pada line
    Melakukan parsing data dari line dengan token dan
    menyimpan hasil parsing dalam bentuk string pada tiap field.
    contoh: parser("sigma;sigma;boy", field, ';'), maka:
    field[0] = "sigma"
    field[1] = "sigma"
    field[2] = "boy"
*/
int parser(char* line,fields* field,char token){
    int fieldIdx = 0, charIdx = 0;
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
    {
        if (line[i] == token)
        {
            field[fieldIdx][charIdx] = '\0';
            fieldIdx++;
            charIdx = 0;
        }
        else
        {
            field[fieldIdx][charIdx] = line[i];
            charIdx++;
        }
    }
    field[fieldIdx][charIdx] = '\0';
    fieldIdx++;
    return fieldIdx;
}


int load_all(char* folder, Denah* denah, UserList* Ulist,
             ObatList* Olist, ObatPenyakitList* OPlist, PenyakitList* Plist) {
    // Cari apakah config terdapat pada path file yang diberikan
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "config.txt");

    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("Folder “%s“ tidak ditemukan.\n", folder);
        exit(1);
    }
    //load
    printf("Loading...\n");
    load_obat(folder, Olist);
    load_user(folder, Ulist);
    load_obatpenyakit(folder, OPlist);
    load_penyakit(folder, Plist);
    load_config(folder, denah, Ulist);
    load_banarich(folder);
    printf("Selamat datang kembali di rumah sakit Nimons!\n");
    return 0;
}


int load_config(char* folder, Denah* denah, UserList* Ulist){
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "config.txt");
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        return 1;
    }
    int _id, size;
    CreateDenah(denah, folder);
    char line[MAX_LINE_LENGTH];
    fields temp[MAX_USER];
    for (int i = 0; i < MAX_USER; i++) {
        linked_create(&(USER(*Ulist,userPosByID(i)).inventoryObat));
    }

    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    denah->M.rows = atoi(temp[0]);
    denah->M.cols = atoi(temp[1]);

    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    denah->maxPasien = atoi(temp[1]);
    denah->maxPerRoom = atoi(temp[0]);

    char ruang[3]; //ASUMSI: Kode ruangan hanya memiliki panjang 2
    ruang[2] = '\0';
    for (int i = 0; i < ROWS(denah->M) * COLS(denah->M); i++) {
        ruang[0] = 'A' + i/denah->M.cols;
        ruang[1] = '1' + i%denah->M.cols;
        denah->M.contents[i/denah->M.cols][i%denah->M.cols] = -1; // Ruang kosong
        fgets(line, sizeof(line), fp);
        size = parser(line, temp, ' ');
        _id = atoi(temp[0]);
        if (_id != 0) {
            denah->M.contents[i/denah->M.cols][i%denah->M.cols] = _id; // Ruang terisi
            map_insert(&RuangtoDokter, ruang, _id);
            strcpy(DOKTER(UserID_to_DokterID(_id)).ruangKerja,ruang);
            //ruang.idDokter[i/denah->M.cols][i%denah->M.cols] = _id;
            for (int j = 0; j < size - 1; j++) {
                if( atoi(temp[j+1]) != 0) {
                    AddPasien_to_Dokter(atoi(temp[j+1]),_id);
                    int dokterID = UserID_to_DokterID(_id);
                    PASIEN(UserID_to_PasienID(atoi(temp[j+1]))).idDokter = dokterID;
                }
            }
        }
    }

    // Load inventory
    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    size = atoi(temp[0]);

    for (int i = 1; i <= size; i++) {
        fgets(line, sizeof(line), fp);
        int count = parser(line, temp, ' ');
        _id = atoi(temp[0]);
        for (int j = 0; j < count - 1; j++) {
            int obatID = atoi(temp[j + 1]);
            linked_insertEnd(&(USER(*Ulist,userPosByID(_id)).inventoryObat), obatID);
            PASIEN(UserID_to_PasienID(_id)).sudahDiobati = 1;
        }
    }


    //Load stack perut
    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    size = atoi(temp[0]);

    for (int i = 1; i <= size; i++) {
        fgets(line, sizeof(line), fp);
        int count = parser(line, temp, ' ');
        _id = atoi(temp[0]);
        for (int j = count-1; j > 0; j--) {
            int obatID = atoi(temp[j]);
            stack_push(&(USER(*Ulist,userPosByID(_id)).perut), obatID);
            PASIEN(UserID_to_PasienID(_id)).sudahDiobati = 1;
        }
    }
    fclose(fp);
    return 0;
}

int load_obat(char* folder, ObatList* l) {
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "obat.csv");
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        perror("Error opening obat.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    // Skip header line first
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Process header if needed
        parser(line, OBAT(*l, cur).field, ';');
        // Don't increment cur, we'll overwrite this with actual data
    }

    // Now process actual data
    while (fgets(line, sizeof(line), fp)) {
        parser(line, OBAT(*l, cur).field, ';');
        cur++;
    }
    l->len = cur;

    fclose(fp);
    return 0;
}

int load_penyakit(char* folder, PenyakitList* l) {
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "penyakit.csv");
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        perror("Error opening penyakit.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    // Skip header line first
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Process header if needed
        parser(line, PENYAKIT(*l, cur).field, ';');
        // Don't increment cur, we'll overwrite this with actual data
    }

    // Now process actual data
    while (fgets(line, sizeof(line), fp)) {
        parser(line, PENYAKIT(*l, cur).field, ';');
        cur++;
    }
    l->len = cur;
    fclose(fp);
    return 0;
}

int load_user(char* folder, UserList* l) {
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "user.csv");

    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        perror("Error opening user.csv");
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    int cur = 1;  // Start at 1 to maintain existing behavior

    // Skip header line first
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Process header if needed
        // Don't increment cur as we're starting from 1
    }

    while (fgets(line, sizeof(line), fp)) {
        int n = parser(line, USER(*l, cur).field, ';');
        if (maxID < atoi(USER(*l, cur).field[0])) maxID = atoi(USER(*l, cur).field[0]);
        for (int i = n; i < 16; i++) {
            strcpy(USER(*l, cur).field[i], "");
        }

        set_insertData(&setUser, username(USER(*l,cur)), atoi(id(USER(*l,cur))));
        l->len++;
        // Masukkan data user ke List berdasarkan role masing masing
        if (strcmp(role(USER(*l, cur)), "dokter") == 0) {
            AddDokterList(atoi(id(USER(*l,cur))));
        }
        else if (strcmp(role(USER(*l,cur)), "pasien") == 0) {
           AddPasienList(atoi(id(USER(*l,cur))));
        }
        else {
            AddManagerList(atoi(id(USER(*l,cur))));
        }
        cur++;
    }
    l->len = cur;
    fclose(fp);
    return 0;
}

int load_obatpenyakit(char* folder, ObatPenyakitList* l) {
    char filePath[MAX_LINE_LENGTH];
    path(filePath, folder, "obat_penyakit.csv");
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        perror("Error opening obat_penyakit.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    // Skip header line first
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Process header if needed
        parser(line, OBATPENYAKIT(*l, cur).field, ';');
        // Don't increment cur, we'll overwrite this with actual data
    }

    // Now process actual data
    while (fgets(line, sizeof(line), fp)) {
        parser(line, OBATPENYAKIT(*l, cur).field, ';');
        cur++;
    }
    l->len = cur;
    fclose(fp);
    return 0;
}

int load_banarich(char* folder){
    char filepath[100];
    path(filepath, folder, "banarich.csv");

    FILE *f = fopen(filepath, "r");
    if (f == NULL) {
        // File tidak ada
        for (int i = 0; i < Ulist.len ; i++) {
            banarich[i] = 0;
        }
        return;
    }

    char line[20];
    int i = 0;
    while (fgets(line, sizeof(line), f) != NULL && i < Ulist.len) {
        banarich[i] = atoll(line); // gunakan atoll untuk long long
        i++;
    }
    fclose(f);
}

void add_user(List *Ulist,Set* Uset){
    char name[MAX_LINE_LENGTH], pass[MAX_LINE_LENGTH];
    printf("username : ");
    scanf("%s", name);
    printf("password : ");
    scanf("%s", pass);
    Set* it = set_findSet(*Uset,name);
    if( it == NULL ){
        set_insertData(Uset, name, Ulist->nEff);
        list_add(Ulist, name);
        printf("Dokter %s berhasil ditambahkan!\n", name);
    }
    else{
        printf("Sudah ada Dokter bernama %s!\n", name);
    }
}

/* SAVE FUNCTIONS */
char fullFolderPath[MAX_LINE_LENGTH];
char command[MAX_LINE_LENGTH];

int save_user(UserList* l) {
    char filePath[MAX_LINE_LENGTH];

    // Buat path file output
    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/user.csv");

    FILE* fp = fopen(filePath, "w");
    int fieldCount = 16;
    
    // Write header first
    fprintf(fp, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;trombosit\n");
    
    // Tulis data ke file
    for (int i = 1; i < l->len; i++) {
        for (int j = 0; j < fieldCount; j++) {
            fprintf(fp, "%s", USER(*l, i).field[j]);
            if (j < fieldCount - 1) {
                fprintf(fp, ";");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

int save_penyakit(PenyakitList* l) {
    char filePath[MAX_LINE_LENGTH];

    // Buat path file output
    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/penyakit.csv");

    FILE* fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Gagal membuka file untuk ditulis");
        return 1;
    }
    int fieldCount = 22;
    
    // Write header first
    fprintf(fp, "id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;tekanan_darah_diastolik_min;tekanan_darah_diastolik_max;detak_jantung_min;detak_jantung_max;saturasi_oksigen_min;saturasi_oksigen_max;kadar_gula_darah_min;kadar_gula_darah_max;berat_badan_min;berat_badan_max;tinggi_badan_min;tinggi_badan_max;kadar_kolesterol_min;kadar_kolesterol_max;trombosit_min;trombosit_max\n");
    
    // Tulis data ke file
    for (int i = 0; i < l->len; i++) {
        for (int j = 0; j < fieldCount; j++) {
            fprintf(fp, "%s", PENYAKIT(*l, i).field[j]);
            if (j < fieldCount - 1) {
                fprintf(fp, ";");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

int save_obat(ObatList* l) {
    char filePath[MAX_LINE_LENGTH];

    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/obat.csv");

    FILE* fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Gagal membuka file untuk ditulis");
        return 1;
    }
    int fieldCount = 2;
    
    // Write header first
    fprintf(fp, "obat_id;nama_obat\n");
    
    // Tulis data ke file
    for (int i = 0; i < l->len; i++) {
        for (int j = 0; j < fieldCount; j++) {
            fprintf(fp, "%s", OBAT(*l, i).field[j]);
            if (j < fieldCount - 1) {
                fprintf(fp, ";");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

int save_obatpenyakit(ObatPenyakitList* l) {
    char filePath[MAX_LINE_LENGTH];
    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/obat_penyakit.csv");

    FILE* fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Gagal membuka file untuk ditulis");
        return 1;
    }
    int fieldCount = 3;
    
    // Write header first
    fprintf(fp, "obat_id;penyakit_id;urutan_minum\n");
    
    // Tulis data ke file
    for (int i = 0; i < l->len; i++) {
        for (int j = 0; j < fieldCount; j++) {
            fprintf(fp, "%s", OBATPENYAKIT(*l, i).field[j]);
            if (j < fieldCount - 1) {
                fprintf(fp, ";");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

void save_banarich() {
    char filePath[MAX_LINE_LENGTH];
    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/banarich.csv");

    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Gagal membuka file untuk ditulis");
        return 1;
    }

    for (int i = 0; i < Ulist.len; i++) {
        fprintf(fp, "%d\n", banarich[i]);
    }
    fclose(fp);
}

void save_config() {
    char filePath[MAX_LINE_LENGTH];
    strcpy(filePath, fullFolderPath);
    strcat(filePath, "/config.txt");

    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Gagal membuka file untuk ditulis");
        return 1;
    }

    fprintf(fp, "%d %d\n", denah.M.rows, denah.M.cols);
    fprintf(fp, "%d %d\n", denah.maxPerRoom, denah.maxPasien);

    for(int i = 0 ; i < denah.M.rows ; i++){
        for(int j = 0 ; j < denah.M.cols ; j++){
            int _id = denah.M.contents[i][j];
            
            if( _id == -1 ) {
                fprintf(fp, "0\n");
                continue;
            }
            
            fprintf(fp, "%s", Ulist.contents[userPosByID(_id)].field[0]);
            Node* tempq = DOKTER(UserID_to_DokterID(_id)).antrian->front;
            
            if( tempq == NULL ) fprintf(fp, " 0\n");
            else{
                while( tempq != NULL ){
                    fprintf(fp, " %d", tempq->data);
                    tempq = tempq->next;
                }
                fprintf(fp, "\n");
            }
        }
    }

    // Inventory
    int cnt = 0;
    for(int i = 0; i < Ulist.len ; i++){
        if( Ulist.contents[i].inventoryObat.size > 0 ) cnt++;
    }

    fprintf(fp, "%d\n", cnt);
    
    for(int i = 0; i < Ulist.len ; i++){
        if( Ulist.contents[i].inventoryObat.size > 0 ) {
            fprintf(fp, "%s", Ulist.contents[i].field[0]);
            Node* cur = Ulist.contents[i].inventoryObat.head;
            while (cur != NULL) {
                fprintf(fp, " %d", cur->data);
                cur = cur->next;
            }
            fprintf(fp,"\n");
        }
    }
    
    // Perut
    cnt = 0;
    for(int i = 0; i < Ulist.len ; i++){
        if( Ulist.contents[i].perut.size > 0 ) cnt++;
    }

    fprintf(fp, "%d\n", cnt);

    for(int i = 0; i < Ulist.len ; i++){
        if( Ulist.contents[i].perut.size > 0 ) {
            fprintf(fp, "%s", Ulist.contents[i].field[0]);
            Node* curr = Ulist.contents[i].perut.top;
            while (curr != NULL) {
                fprintf(fp, " %d", curr->data);
                curr = curr->next;
            }
            fprintf(fp,"\n");
        }
    }
    
    fclose(fp);
}

// TODO : Simpan config
int save_all(char* folderName,ObatList* obatList,ObatPenyakitList* obatPenyakitList,
            PenyakitList* penyakitList,UserList* userList){
    // Cek apakah folder data/ ada
    int dataExists = folder_exists("data");

    // Buat path folder lengkap: data/nama_folder
    strcpy(fullFolderPath, "data/");
    strcat(fullFolderPath, folderName);

    // Cek apakah folder data/nama_folder ada
    int subfolderExists = folder_exists(fullFolderPath);

    printf("\nSaving...\n");

    if (!dataExists) {
        printf("\nMembuat folder data...\n");
        system("mkdir data");
    }

    if (!subfolderExists) {
        printf("Membuat folder %s...\n", fullFolderPath);
        // Buat perintah mkdir data/nama_folder
        strcpy(command, "mkdir ");
        strcat(command, fullFolderPath);
        system(command);
    }
    
    save_obat(obatList);
    save_obatpenyakit(obatPenyakitList);
    save_penyakit(penyakitList);
    save_user(userList);
    save_banarich();
    save_config();
    printf("Berhasil menyimpan data di folder %s!\n", fullFolderPath);
    return 0;
}