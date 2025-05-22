#include "../header/file/user.h"
#include "../header/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 100

char *ParseData(char *line, int *i, char token) {
    char *data = (char *)malloc(MAX_FIELD_LENGTH * sizeof(char));
    if (data == NULL) return NULL;

    int idx = 0;
    while (line[*i] != token && line[*i] != '\n' && line[*i] != '\0') {
        data[idx++] = line[*i];
        (*i)++;
    }

    data[idx] = '\0'; // null-terminate
    if (line[*i] == token) {
        (*i)++; // lewati token
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
    strcpy( &newUser->field[3] , "Pasien" );

    free(temp);
    uList->len = uList->len + 1;
}

void MenuLihat (UserList uList, char *prompt) {
	int urutan;
	if (strcmp(prompt, "LIHAT_USER") == 0) {
		LihatUser(uList);
	} else if (strcmp(prompt, "LIHAT_DOKTER") == 0) {
		LihatDokter(uList);
	} else if (strcmp(prompt, "LIHAT_PASIEN") == 0) {
		LihatPasien(uList);
	} 
}

char* ToLower(char *str) {
    char* lowerstr = (char*)malloc(strlen(str) + 1);
	strcpy(lowerstr, str);

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			lowerstr[i] = str[i] + 32;
		}
	}
	return lowerstr;
}

void LihatUser (UserList uList) {
	int urutan, sort;

	printf("Basis pengurutan: \n");
	printf("1. ID\n");
	printf("2. Nama\n");
	do {
		printf(">>> Pilihan: ");
		scanf("%d", &urutan);
		if (urutan != 1 && urutan != 2) printf("Pilihan tidak valid\n");
	} while (urutan != 1 && urutan != 2);

	char urutanLihat[20];
	if (urutan == 1) strcpy(urutanLihat, "ID");
	else if (urutan == 2) strcpy(urutanLihat, "Nama");

	printf("Metode pengurutan: \n");
	printf("1. ASC (A-Z)\n");
	printf("2. DESC (Z-A)\n");
	do {
		printf(">>> Pilihan: ");
		scanf("%d", &sort);
		if (sort != 1 && sort != 2) printf("Pilihan tidak valid\n");
	} while (sort != 1 && sort != 2);

	char sortLihat[20];
	if (sort == 1) strcpy(sortLihat, "ascending");
	else if (sort == 2) strcpy(sortLihat, "descending");
	
	printf("Menampilkan semua pengguna dengan %s terurut %s...\n", urutanLihat, sortLihat);
	printf("|-ID-|-----Nama-----|---Role---|----Penyakit----|\n");
	printf("=================================================\n");
	
	UserList sorted;
	length(sorted) = length(uList);
	for (int i = 0; i < length(uList); i++) {
		sorted.contents[i] = uList.contents[i];
	}

	for (int i = 0; i < length(sorted) - 1; i++) {
		for (int j = 0; j < length(sorted) - i - 1; j++) {
			if (urutan == 1) {
				if (sort == 1) {
					if (atoi(id(sorted.contents[j])) > atoi(id(sorted.contents[j + 1]))) {
						User temp = sorted.contents[j];
						sorted.contents[j] = sorted.contents[j + 1];
						sorted.contents[j + 1] = temp;
					}
				} else if (sort == 2) {
					if (atoi(id(sorted.contents[j])) < atoi(id(sorted.contents[j + 1]))) {
						User temp = sorted.contents[j];
						sorted.contents[j] = sorted.contents[j + 1];
						sorted.contents[j + 1] = temp;
					}
				}
			} else if (urutan == 2) {
				char* lowerCurrent = ToLower(username(sorted.contents[j]));
				char* lowerNext = ToLower(username(sorted.contents[j + 1]));
				if (sort == 1) {
					if (strcmp(lowerCurrent, lowerNext) > 0) {
						User temp = sorted.contents[j];
						sorted.contents[j] = sorted.contents[j + 1];
						sorted.contents[j + 1] = temp;
					}
				} else if (sort == 2) {
					if (strcmp(lowerCurrent, lowerNext) < 0) {
						User temp = sorted.contents[j];
						sorted.contents[j] = sorted.contents[j + 1];
						sorted.contents[j + 1] = temp;
					}
				}
			}
		}
	}
	for (int i = 0; i < length(sorted); i++) {
		if ((strcmp(role(sorted.contents[i]), "Dokter") == 0) || (strcmp(role(sorted.contents[i]), "Manager") == 0)) {
			printf("|%3d| %-12s | %-8s |       -        |\n", atoi(id(sorted.contents[i])), username(sorted.contents[i]), role(sorted.contents[i]));
		} else {
			printf("|%3d| %-12s | %-8s | %-14s |\n", atoi(id(sorted.contents[i])), username(sorted.contents[i]), role(sorted.contents[i]), riwayat(sorted.contents[i]));
		}
	}
}

void LihatDokter (UserList uList) {
	return;
}

void LihatPasien (UserList uList) {
	return;
}