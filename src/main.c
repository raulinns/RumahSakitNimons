// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/file/user.h"
#include "header/login.h"
#include "header/denah.h"
#include "header/user.h"
#include "header/password.h"
#include "header/file-utilities.h"
#include "header/adt/set.h"
#include "header/adt/list.h"
#include "header/diagnosis.h"
#include "header/ngobatin.h"
#include "header/minum-obat.h"
#include "header/hospital.h"
#include "header/pulang.h"

Set setUser;
List listUser;
UserList Ulist;
ObatList Olist;
ObatPenyakitList OPlist;
PenyakitList Plist;
Denah denah;
Ruangan ruangan;
ListRuangan listRuangan;
Map antrean;

void init(){
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
		exit(0);
    }

    load_all(argv[1], &denah, &antrean, &Ulist, &Olist, &OPlist, &Plist);
    int exit = 0, loggedIn = 0, i;
    do {
		printf("========================================\n");
		printf(">>> ");
		scanf("%s", prompt);
		if (strcmp(prompt,"LOGIN") == 0) {
        	if (loggedIn != 0) //melakukan login saat sudah loggedin
        	{
        	    printf("Anda sudah login dengan username %s\n", user);
        	}
        	else 
        	{
        	    loggedIn = login(Ulist);
        	}
		} else if(strcmp(prompt,"LOGOUT") == 0) {
        	if (loggedIn = 0) //melakukan logout saat belum loggedin
        	{
        	    printf("Anda belum login\n");
        	}
        	else
        	{
        	    setUser = NULL;
				for (int i = 0; i < 1001; i++)
				{
					user[i] = '\0';
					pass[i] = '\0';
				}
				
				loggedIn = 0;
        	}
    	} else if( strcmp(prompt,"REGISTER") == 0) { // NEED FIX (KLOCE)
        	if (loggedIn != 0) //melakukan register saat sudah loggedin
        	{
        	    printf("Anda sudah login dengan username %s\n", user);
        	}
        	else
        	{
        	    loggedIn = Register(&Ulist);
        	}
    	} else if (strcmp(prompt,"LUPA_PASSWORD") == 0) {  // UNTESTED
			if (loggedIn == 0) //melakukan reset password saat sudah belum loggedin
			{
				printf("Anda belum login\n");
			}
			else
			{
				//passwordUpdate();
			}
    	} else if (strcmp(prompt, "LIHAT_DENAH") == 0) {
			if (loggedIn == 0) //melakukan register saat sudah loggedin
			{
				printf("Anda belum login\n");
				
			}
			else
			{
				PrintDenah(denah);
			}
		} else if (strcmp(prompt,"LIHAT_RUANGAN") == 0) { //NEED FIX (KLOCE)
            char ruang[5];
            scanf("%s", ruang);
            strcat(prompt," ");
            strcat(prompt,ruang);
			if (loggedIn == 0) //melakukan reset password saat sudah belum loggedin
			{
				printf("Anda belum login\n");
			}
			else
			{
				PrintRuang(prompt, denah);
			}
		} else if (strcmp(prompt,"UBAH_DENAH") == 0) { // UNTESTED
			if (loggedIn == 1) //melakukan register saat sudah loggedin
			{
				UbahDenah(prompt, &denah);
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		} else if (strcmp(prompt,"DIAGNOSIS") == 0) { // UNTESTED
			if (loggedIn == 2)
			{
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++)
				{
					if (strcmp(Ulist.contents[i].field[1], user) == 0)
					{
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				DIAGNOSIS(currentDokter, listRuangan, &Ulist, &Plist);
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		} else if (strcmp(prompt,"NGOBATIN") == 0) { // UNTESTED
			if (loggedIn == 2)
			{
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++)
				{
					if (strcmp(Ulist.contents[i].field[1], user) == 0)
					{
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				NGOBATIN(currentDokter, listRuangan, &Ulist, &OPlist);
			}
		} else if (strcmp(prompt, "PULANGDOK") == 0) { //UNTESTED
			switch (loggedIn)
			{
				case 0:
				printf("Anda belum login\n");
				break;
				case 3:
				User Pasien;
				for (int i = 0; i != Ulist.len; i++) {
					if (strcmp(Ulist.contents[i].field[1], user) == 0) {
						Pasien = Ulist.contents[i];
						break;
					}
				}
				pulangdok(Pasien, OPlist, Olist);
				break;
				default:
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		else if (strcmp(prompt,"MINUM_OBAT") == 0) {
			if (loggedIn == 0){ //melakukan reset password saat sudah belum loggedin
				printf("Anda belum login\n");
			} 
			else if (loggedIn == 1){ //saat sudah loggedin
				User currentPasien;
				for (int i = 0; i < Ulist.len; i++){
					if (strcmp(Ulist.contents[i].field[1], user) == 0)
					{
						currentPasien = Ulist.contents[i];
						break;
					}
				}
				minumObat(&currentPasien, &Olist);
			}
		} else if (strcmp(prompt,"PENAWAR") == 0){
			if (loggedIn == 0){ //melakukan reset password saat sudah belum loggedin
				printf("Anda belum login\n");
			} 
			else if (loggedIn == 1){ //saat sudah loggedin
				User currentPasien;
				for (int i = 0; i < Ulist.len; i++){
					if (strcmp(Ulist.contents[i].field[1], user) == 0)
					{
						currentPasien = Ulist.contents[i];
						break;
					}
				}
				minumPenawar(&currentPasien, &Olist);
			}
		} else if (strcmp(prompt,"HELP") == 0) {
			printf("=========== HELP ===========\n");
			switch (loggedIn)
			{
			case 0:
				printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
				printf("    1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
				printf("    2. REGISTER: Membuat akun baru\n");
				break;
			case 1:
				printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager,\n tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", user);
				printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
				printf("    2. LIHAT_DENAH: \n");
				printf("    3. LIHAT_RUANGAN: \n");
				printf("    4. UBAH_DENAH: \n");
				break;
			case 2:
				printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", user);
				printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
				printf("    2. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
				printf("    3. LIHAT_DENAH: \n");
				printf("    4. LIHAT_RUANGAN: \n");
				printf("    5. UBAH_DENAH: \n");
				break;
			case 3:
				printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", user);
				printf("    1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
				printf("    2. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
				printf("    3. LIHAT_DENAH: \n");
				printf("    4. LIHAT_RUANGAN: \n");
				printf("    5. UBAH_DENAH: \n");
				break;
			}
			printf("\n");
			if (loggedIn != 1)
			{
				printf("Footnote:\n");
				printf("    1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
				printf("    2. Jangan lupa untuk memasukkan input yang valid\n\n");
			}
		} else if (strcmp(prompt, "EXIT") == 0) {
			exitProgram(&exit);
			exit = 1;
		} else if (strcmp(prompt, "SAVE") == 0){
			char folderName[100]; // Panjang nama folder diasumsikan <= 100
			printf("\nMasukkan nama folder: ");
    		scanf("%s", folderName);
			save_all(folderName, &Olist, &OPlist, &Plist, &Ulist);
		} else {
			printf("Perintah tidak valid. Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
		}
	} while (exit == 0);
}

// TODO : Nambahin user di adt jangan di file eksternal
//        Ngerjain LIHAT_ANTREAN
