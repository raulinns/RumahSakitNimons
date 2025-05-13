// Include any necessary headers
#include <stdio.h>
#include <string.h>
// #include "header/login.h"
#include "header/denah.h"
// #include "header/user.h"
// #include "header/password.h"
#include "header/file-utilities.h"
// #include "header/adt/set.h"
// #include "header/adt/list.h"

Set setUser;
List listUser;
UserList Ulist;
ObatList Olist;
ObatPenyakitList OPlist;
PenyakitList Plist;
Denah denah;
Map antrean;

void init(){///??????
    setUser = NULL;
    list_create(&listUser);
}

int main(int argc, char* argv[])
{
    init();
    char prompt[1001];
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
    }
    load_all(argv[1], &denah, &antrean, &Ulist, &Olist, &OPlist, &Plist);
    printf("%d %d\n", denah.M.rows, denah.M.cols);
    for(int i = 1 ; i <= 15 ; i++){
        if( map_findMap(antrean, i) != NULL){
            Map x = map_findMap(antrean,i);
            printf("ID : %d, ROOM : %d\n", x->key, x->room);
            printf("Queue: ");
            queue_print(&x->data);
        }
    }
    // Denah denah; int i = 0;
    // CreateDenah(&denah);
    // printf("========================================\n");
    // printf(">>> ");
    // scanf("%s", prompt);
    // int exit = 0, logged_in = 0;
    // while( exit == 0 ){
    //     // if (strcmp(prompt,"LOGIN") == 0){
    //     //     login();
    //     // }

    //     // if( strcmp(prompt,"REGISTER") == 0){
    //     //     Register();
    //     // }

    //     // if (strcmp(prompt, "LIHAT_DENAH") == 0) {
    //     //     PrintDenah(denah);
    //     // }

    //     // if (strcmp(ParseData(prompt, i, ' '), "LIHAT_RUANGAN") == 0) {
    //     //     PrintRuang(prompt, denah);
    //     // }

    //     // if (strcmp(ParseData(prompt, i, ' '), "UBAH_DENAH") == 0) {
    //     //     UbahDenah(prompt, &denah);
    //     // }

    //     // if (strcmp(prompt,"LUPA_PASSWORD") == 0){
    //     //     passwordUpdate();
    //     // }

    //     // if (strcmp(prompt,"TAMBAH_DOKTER") == 0){
    //     //     add_user(&listUser,&setUser);
    //     // }

    //     // if (strcmp(prompt, "EXIT") == 0){
    //     //     exit = 1;
    //     // }
    // }
}