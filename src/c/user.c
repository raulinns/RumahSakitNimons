#include "../header/file/ext-list.h"
#include "../header/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/adt/set.h"
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

// int IdxUser(char *name){
//     FILE *userfile = fopen("data/user.csv","r");
//     if (userfile == NULL)
//     {
//         perror("Error opening file");
//         return -1;
//     }
//     char line[MAX_LINE_LENGTH];
//     char fields[MAX_FIELDS][MAX_FIELD_LENGTH];

//     while (fgets(line, sizeof(line), userfile))
//     {
//         int field_idx = 0, char_idx = 0;
//         for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
//         {
//             if (line[i] == ';') //parsing dengan pembeda ";"
//             {
//                 fields[field_idx][char_idx] = '\0'; // end current field
//                 field_idx++;
//                 char_idx = 0;
//             }
//             else
//             {
//                 fields[field_idx][char_idx++] = line[i];
//             }
//         }
//         fields[field_idx][char_idx] = '\0'; // terminate last field
//         field_idx++;

//         //Checking valid username
//         if (strcmp(name,fields[1]) == 0)
//         {
//             return atoi(fields[0]);
//         }
//     }
    
//     fclose(userfile);

//     return -1;
// }

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
    int len = uList->len;
    char* temp = to_string(len);
    User* newUser = &uList->contents[uList->len];

    strcpy( &newUser->field[0] , temp );
    strcpy( &newUser->field[1] , name );
    strcpy( &newUser->field[2] , pass );
    strcpy( &newUser->field[3] , "pasien" );

    free(temp);
    uList->len = uList->len + 1;
}


int AddDokter(UserList* uList){
    char user[1001], pass[1001];
    printf("Username: ");
    scanf("%s", user);
    if( set_contains(setUser, user) == 1 ) // User dengan nama yang sama sudah ada
    {
        printf("Sudah ada Dokter bernama %s!\n", user);
        return 0;
    }

    printf("Pass: ");
    scanf("%s", pass);

    /* Menambahkan data user baru pada user.csv */
    int len = uList->len;
    char* temp = to_string(len);
    User* newUser = &uList->contents[uList->len];
    set_insertData(&setUser, user, uList->len);

    strcpy( &newUser->field[0] , temp );
    strcpy( &newUser->field[1] , user );
    strcpy( &newUser->field[2] , pass );
    strcpy( &newUser->field[3] , "Dokter" );

    free(temp);
    uList->len = uList->len + 1;
    AddDokterList(uList->len-1);
    printf("Dokter %s berhasil ditambahkan!\n", user);
    return 1;
}
