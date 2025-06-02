#include "../header/file/ext-list.h"
#include "../header/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/adt/set.h"
#include "../header/login.h"
#include "role.h"

#define MAX_FIELD_LENGTH 100

Set setUser;

char *ParseData(char *line, int *i, char token) {
    char *data = (char *)malloc(MAX_FIELD_LENGTH * sizeof(char));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed in ParseData\n");
        return NULL;
    }
    
    int idx = 0;
    // Skip leading whitespace
    while (line[*i] == ' ' || line[*i] == '\t') {
        (*i)++;
    }
    
    // Parsing sampai ketemu token
    while (line[*i] != token && line[*i] != '\n' && line[*i] != '\0' && line[*i] != '\r') {
        if (idx >= MAX_FIELD_LENGTH - 1) {
            fprintf(stderr, "Field too long in ParseData\n");
            break;
        }
        data[idx++] = line[*i];
        (*i)++;
    }
    
    data[idx] = '\0'; // null-terminate
    
    // Lewati token
    if (line[*i] == token) {
        (*i)++;
    }
    

    return data;
}

char *NamaUser(int idx) {
    FILE *userFile = fopen("../data/user.csv", "r");
    char name[MAX_FIELD_LENGTH], line[MAX_LINE_LENGTH];
    int id, i;
    while (id != idx) {
        fgets(line, MAX_LINE_LENGTH, userFile);
        i = 0;
        id = atoi(ParseData(line, i, ';'));
    }
    fclose(userFile);
    int temp = i;
    strcpy(name, ParseData(line, i, ';'));
    return name;
}

char* to_string(int value) {
    char* buffer = malloc(12 * sizeof(char)); 
    if (buffer != NULL) {
        snprintf(buffer, 12, "%d", value);
    }
    return buffer;
}

void AddUser(char *name, char *pass, UserList *uList){
    char* temp = to_string(maxID);
    User* newUser = &uList->contents[uList->len];

    strcpy( &newUser->field[0] , temp );
    strcpy( &newUser->field[1] , name );
    strcpy( &newUser->field[2] , pass );
    strcpy( &newUser->field[3] , "pasien" );
    banarich[uList->len] = 0;

    free(temp);
    uList->len = uList->len + 1;
}


int AddDokter(UserList* uList){
    char user[1001], pass[1001];
    printf("Username: ");
    scanf("%s", user);
    if( set_contains(setUser, user) == 1 ) // User dengan nama yang sama sudah ada
    {
        printf("Sudah ada user bernama %s!\n", user);
        return 0;
    }

    printf("Pass: ");
    scanf("%s", pass);

    /* Menambahkan data user baru pada user.csv */
    maxID++;
    int len = uList->len;
    char* temp = to_string(maxID);
    User* newUser = &uList->contents[uList->len];
    set_insertData(&setUser, user, maxID);

    strcpy( &newUser->field[0] , to_string(maxID) );
    strcpy( &newUser->field[1] , user );
    strcpy( &newUser->field[2] , pass );
    strcpy( &newUser->field[3] , "dokter" );
    banarich[uList->len] = 0;

    free(temp);
    uList->len = uList->len + 1;
    AddDokterList(maxID);

    printf("Dokter %s berhasil ditambahkan!\n", user);
    return 1;
}
