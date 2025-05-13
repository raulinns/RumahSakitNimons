#include "../header/adt/map.h"
#include "../header/file-utilities.h"
#include "../header/denah.h"
#include <string.h>


void path(char* dest, const char* dir, const char* name){
    strcpy(dest, "data/");
    strcat(dest, dir);
    strcat(dest, "/");
    strcat(dest, name);
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
            field[fieldIdx][charIdx++] = line[i];
        }
    }
    field[fieldIdx][charIdx] = '\0';
    fieldIdx++;
    return fieldIdx;
}


int load_all(char* folder, Denah* denah, Map* map, UserList* Ulist,
             ObatList* Olist, ObatPenyakitList* OPlist, PenyakitList* Plist) {
    if (load_config(folder, denah, map, Ulist)) {
        printf("Folder “%s“ tidak ditemukan.\n", folder);
        exit(1);
    }
    printf("Loading...\n");
    load_obat(folder, Olist);
    load_user(folder, Ulist);
    load_obatpenyakit(folder, OPlist);
    load_penyakit(folder, Plist);
    printf("Selamat datang kembali di rumah sakit Nimons!\n");
    return 0;
}


int load_config(char* folder, Denah* denah, Map* map, UserList* Ulist){
    char filepath[MAX_LINE_LENGTH];
    path(filepath, folder, "config.txt");
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening config.txt");
        return 1;
    }
    int id, size;
    CreateDenah(denah, folder);
    char line[MAX_LINE_LENGTH];
    fields temp[MAX_USER];
    for (int i = 0; i < MAX_USER; i++) {
        linked_create(&(USER(*Ulist, i).inventoryObat));
    }

    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    denah->M.rows = atoi(temp[0]);
    denah->M.cols = atoi(temp[1]);

    fgets(line, sizeof(line), fp);
    parser(line, temp, ' ');
    denah->maxPasien = atoi(temp[0]);

    for (int i = 0; i < ROWS(denah->M) * COLS(denah->M); i++) {
        fgets(line, sizeof(line), fp);
        size = parser(line, temp, ' ');
        id = atoi(temp[0]);
        if (id != 0) {
            for (int j = 0; j < size - 1; j++) {
                map_insertData(map, id, atoi(temp[j + 1]), i);
            }
        }
    }

    fgets(line, sizeof(line), fp);
    parser(line, temp, ';');
    size = atoi(temp[0]);

    for (int i = 1; i < size; i++) {
        fgets(line, sizeof(line), fp);
        int count = parser(line, temp, ';');
        id = atoi(temp[0]);

        for (int j = 0; j < count - 1; j++) {
            int obatID = atoi(temp[j + 1]);
            linked_insertEnd(&(USER(*Ulist, id).inventoryObat), obatID);
            //map_insertData(map, id, obatID);
        }
    }

    fclose(fp);
    return 0;
}

int load_obat(char* folder, ObatList* l) {
    char filepath[MAX_LINE_LENGTH];
    path(filepath, folder, "obat.csv");
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening obat.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    while (fgets(line, sizeof(line), fp)) {
        parser(line, OBAT(*l, cur).field, ';');
        cur++;
    }

    fclose(fp);
    return 0;
}

int load_penyakit(char* folder, PenyakitList* l) {
    char filepath[MAX_LINE_LENGTH];
    path(filepath, folder, "penyakit.csv");
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening penyakit.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    while (fgets(line, sizeof(line), fp)) {
        parser(line, PENYAKIT(*l, cur).field, ';'); // <- asumsi field[cur] valid
        cur++;
    }

    fclose(fp);
    return 0;
}


int load_user(char* folder, UserList* l) {
    char filepath[MAX_LINE_LENGTH];
    path(filepath, folder, "user.csv");
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening user.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    while (fgets(line, sizeof(line), fp)) {
        parser(line, USER(*l, cur).field, ';');
        cur++;
    }

    fclose(fp);
    return 0;
}


int load_obatpenyakit(char* folder, ObatPenyakitList* l) {
    char filepath[MAX_LINE_LENGTH];
    path(filepath, folder, "obat-penyakit.csv");
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening obat-penyakit.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int cur = 0;

    while (fgets(line, sizeof(line), fp)) {
        parser(line, OBATPENYAKIT(*l, cur).field, ';');
        cur++;
    }

    fclose(fp);
    return 0;
}


int addUserList(char *name, char *pass,UserList *Ulist){
    FILE * fp = fopen("data/user.csv","a");
    fprintf(fp, ";%s;%s;;;;;;;;;;;;;\n", name, pass);
    fclose(fp);
    return 0;
}

int add_obat(char name, char *pass){

}

//FITUR:
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


int add_penyakit(){

}