// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/denah.h"
#include "header/file/ext-list.h"
#include "header/login.h"
#include "header/user.h"
#include "header/password.h"
#include "header/file-utilities.h"
#include "header/adt/set.h"
#include "header/adt/list.h"
#include "header/role.h"
#include "header/lihat-cari.h"
#include "header/diagnosis.h"
#include "header/ngobatin.h"
#include "header/minum-obat.h"
#include "header/hospital.h"
#include "header/pulang.h"

/* List external:
	UserList Ulist;
	ObatList Olist;
	ObatPenyakitL
	map_createist OPlist;
	PenyakitList Plist;
	Denah denah;
*/

Ruangan ruangan;
ListRuangan listRuangan;
void init(){
	pasienList.neff  = 0;
	managerList.neff = 0;
	dokterList.neff = 0;
	setUser = NULL;
	for(int i = 0 ; i < MAX_USER ; i++){
		DOKTER(i).antrian = malloc(sizeof(Queue));
		queue_create(DOKTER(i).antrian);
	}
	RuangtoDokter = NULL;
}

void printLogo() {
	printf("==================================================================================================\n");
	printf("||                                                                                              ||\n");
    printf("||  ██████     ███████       ███    ██    ██    ███    ███     ██████     ███    ██    ███████  ||\n");
	printf("||  ██   ██    ██            ████   ██    ██    ████  ████    ██    ██    ████   ██    ██       ||\n");
	printf("||  ██████     ███████       ██ ██  ██    ██    ██ ████ ██    ██    ██    ██ ██  ██    ███████  ||\n");
	printf("||  ██   ██         ██       ██  ██ ██    ██    ██  ██  ██    ██    ██    ██  ██ ██         ██  ||\n");
	printf("||  ██   ██    ███████       ██   ████    ██    ██      ██     ██████     ██   ████    ███████  ||\n");
	printf("||                                                                                              ||\n");
	printf("==================================================================================================\n");
	printf("Selamat datang di aplikasi Rumah Sakit Nimons!\n");
	printf("Silahkan masukkan perintah yang diinginkan.\n");
	printf("Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
}

int main(int argc, char* argv[])
{
    init();
    char input[1001];
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
		exit(0);
    }
    load_all(argv[1], &denah, &Ulist, &Olist, &OPlist, &Plist);
    int exit = 0, loggedIn = 0, i;
    do {
		printf("\n==================================================================================================\n");
		printf(">>> ");
		scanf("%s", input);

		char* prompt = ToUpper(input);

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
				printf("Anda berhasil logout!\n");
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
		} else if(strcmp(prompt,"ANTRIAN") == 0){ // Belum ditambahin checker role - TESTED
			CekAntrian(masterID);
		} else if(strcmp(prompt,"DAFTAR_CHECKUP") == 0){
			DaftarCheckup();
		}
		else if (strcmp(prompt,"LIHAT_RUANGAN") == 0) { // - TESTED Kloce
			if (loggedIn == 0) //melakukan reset password saat sudah belum loggedin
			{
				printf("Anda belum login\n");
			}
			else
			{
				char ruang[5]; //ASUMSI : ruang hanya menggunakan 2 char
    			scanf("%s", ruang);
				PrintRuang(denah,ruang,0);
			}
		} else if (strcmp(prompt, "LIHAT_SEMUA_ANTRIAN") == 0){ // Belum ditambahin checker role - UNTESTED
				PrintDenah(denah); printf("\n");
				char ruang[5];
				Map ptr;
				ruang[0] = 'A';
				ruang[2] = '\0';
				for(int i = 0; i < denah.M.rows ; i++){
					ruang[1] = '1'; //ASUMSI: MAXLEN RUANG ADALAH 2
					for(int j = 0 ; j < denah.M.cols ; j++){
						ptr = map_findMap(RuangtoDokter, ruang);
						if( ptr != NULL ){
							PrintRuang(denah, ruang, 1);
							printf("\n");
						}
						ruang[1]++;
					}
					ruang[0]++;
				}
		}else if (strcmp(prompt,"UBAH_DENAH") == 0) { // UNTESTED
			if (loggedIn == 1) //melakukan register saat sudah loggedin
			{
				UbahDenah(prompt, &denah);
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		} else if(strcmp(prompt,"TAMBAH_DOKTER") == 0){
			AddDokter(&Ulist);
		} else if(strcmp(prompt,"ASSIGN_DOKTER") == 0){
			AssignDokter();
		}else if (strcmp(prompt,"HELP") == 0) {
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
				printf("    5. LIHAT_USER: Melihat daftar user yang terdaftar\n");
				printf("    6. LIHAT_DOKTER: Melihat daftar dokter yang terdaftar\n");
				printf("    7. LIHAT_PASIEN: Melihat daftar pasien yang terdaftar\n");
				printf("    8. CARI_USER: Mencari user berdasarkan ID atau nama\n");
				printf("    9. CARI_DOKTER: Mencari dokter berdasarkan ID atau nama\n");
				printf("    10. CARI_PASIEN: Mencari pasien berdasarkan ID, nama, atau penyakit\n");
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

		} else if (strcmp(prompt, "LIHAT_USER") == 0 || (strcmp(prompt, "LIHAT_DOKTER") == 0) || (strcmp(prompt, "LIHAT_PASIEN") == 0)) {
			if (loggedIn == 0)
			{
				printf("Anda belum login\n");
			}
			else if (loggedIn == 1)
			{
				PilihanLihat(Ulist, prompt);
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}

		} else if (strcmp(prompt, "CARI_USER") == 0 || (strcmp(prompt, "CARI_DOKTER") == 0) || (strcmp(prompt, "CARI_PASIEN") == 0)) {
			if (loggedIn == 0)
			{
				printf("Anda belum login\n");
			}
			else if (loggedIn == 1)
			{
				PilihanCari(Ulist, prompt);
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}

		} else if(strcmp(prompt, "SKIP_ANTRIAN") == 0){
			SkipAntrian();
		} else if(strcmp(prompt, "CANCEL_ANTRIAN") == 0){
			KeluarAntrian();
		}else if (strcmp(prompt, "LOGOUT") == 0) {
			loggedIn = 0;
			printf("Anda telah logout dari akun %s\n", user);

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

//TODO : update all headers (currently features work fine)