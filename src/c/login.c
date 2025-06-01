#include "../header/file/ext-list.h"
#include "../header/login.h"
#include "../header/password.h"
#include "../header/role.h"
#include <stdlib.h>

char user[1001], pass[1001];
int maxID;

int getIDbyName(UserList uList,char* name){
    for(int i = 0 ; i < uList.len ; i++) if(strcmp(name,username(USER(Ulist,i))) == 0) return i;
    return -1;
}

int findID(UserList uList, char* name){
    for(int i = 0 ; i < uList.len ; i++) if(strcmp(name,username(USER(Ulist,i))) == 0) return atoi(id(USER(Ulist,i)));
    return -1;
}

int login(UserList uList)
{
    int validuser = 0,validpass = 0;
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);
    int check = getIDbyName(uList,user);
    if( check == -1 ){
        printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n",user);
        login(uList);
    }
    // Check wheter a user with the inputted name exist
    if ( strcmp( username(USER(Ulist,check) )  , user ) == 0)
    {
        if ( strcmp( password(USER(Ulist,check) ) , pass ) == 0)
        {
            masterID = findID(uList, user);
            if (strcmp(role(USER(Ulist,check)),"manager") == 0)
            {
                printf("Selamat pagi Manager %s!\n",user);
                return 1;
            }
            else if (strcmp(role(USER(Ulist,check)),"dokter") == 0)
            {
                printf("Selamat pagi Dokter %s!\n",user);
                return 2;
            }
            else if (strcmp(role(USER(Ulist,check)),"pasien") == 0)
            {
                printf("Selamat pagi %s! Ada keluhan apa ?\n",user);
                return 3;
            }

        }
        else //Username found && Password not found
        {
            printf("Password salah untuk pengguna yang bernama %s!\n",user);
            login(uList);
        }
    }
}


// Otomatis jadi pasien
int Register(UserList* uList){
    printf("Username: ");
    scanf("%s", user);
    if( getIDbyName(*uList,user) != -1 ) // User dengan nama yang sama sudah ada
    {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", user);
        return 0;
    }

    printf("Pass: ");
    scanf("%s", pass);

    /* Menambahkan data user baru pada user.csv */
    maxID++;
    AddUser(user,pass, uList);
    AddPasienList(maxID);
    masterID = maxID;
    printf("Selamat pagi %s! Ada keluhan apa ?\n", user);
    return 3;
}

int passwordUpdate(){
    
    char username[1001],new_pass[1001], code[1001];
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
    printf("Username: ");
    scanf("%s", username);
    printf("Kode Unik: ");
    scanf("%s", code);
    User* user = NULL;
    for(int i = 0 ; i < Ulist.len ; i++){
        if( strcmp(Ulist.contents[i].field[1],username) == 0 ) {user = &Ulist.contents[i]; break;}
    }
    int validuser = 0;

    //Validasi username dan kode unik
    if (user != NULL){
        char* encoded = runLengthEncoding(user->field[1]);
        if(strcmp(code, encoded) == 0){       
            if (strcmp(user->field[3],"manager") == 0)
            {
                printf("Halo manager %s, silakan daftarkan ulang password anda!\n", username);
            }
            else if (strcmp(user->field[3],"dokter") == 0)
            {
                printf("Halo dokter %s, silakan daftarkan ulang password anda!\n", username);
            }
            else if (strcmp(user->field[3],"pasien") == 0)
            {
                printf("Halo pasien %s, silakan daftarkan ulang password anda!\n", username);
            }
            printf("Password Baru: ");
            scanf("%s", new_pass);
            strcpy(user->field[2],new_pass);
            free(encoded);
        }
        else
        {
            printf("Kode unik salah!\n");
        }
    } else{
        printf("Username tidak terdaftar!\n"); 
    }
    return 0;
}