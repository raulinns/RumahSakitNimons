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

void init();
void printLogo();
void help();

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
		printf("\n");
		printLogo(); 
		printf("\n");
		printf("==================================================================================================\n");
		printf(">>> ");
		scanf("%s", input);
		
		char* prompt = ToUpper(input);
		
		if (strcmp(prompt,"LOGIN") == 0) {
			if (loggedIn != 0) {
				printf("Anda sudah login dengan username %s\n", user);
        	}
        	else {
				loggedIn = login(Ulist);
        	}
		} 
		
		else if (strcmp(prompt,"REGISTER") == 0) {
			if (loggedIn != 0) {
				printf("Anda sudah login dengan username %s\n", user);
			}
			else {
				loggedIn = Register(&Ulist);
			}
			
		} 
		
		else if (strcmp(prompt,"LOGOUT") == 0) {
			if (loggedIn = 0) {
				printf("Anda belum login\n");
        	}
        	else {
				setUser = NULL;
				for (int i = 0; i < 1001; i++)
				{
					user[i] = '\0';
					pass[i] = '\0';
				}
				printf("Anda berhasil logout!\n");
				loggedIn = 0;
        	}
    	} 
		
		else if (strcmp(prompt,"LUPA_PASSWORD") == 0) { 
			passwordUpdate();
    	} 
		
		else if (strcmp(prompt,"HELP") == 0) {
			help(loggedIn);
		} 
		
		else if (strcmp(prompt, "LIHAT_DENAH") == 0) {
			if (loggedIn == 0) {
				printf("Anda belum login\n");	
			}
			else {
				PrintDenah(denah);
			}
		} 
		
		else if (strcmp(prompt,"LIHAT_RUANGAN") == 0) {
			if (loggedIn == 0) {
				printf("Anda belum login\n");
			}
			else {
				char ruang[5]; //ASUMSI : ruang hanya menggunakan 2 char
    			scanf("%s", ruang);
				PrintRuang(denah,ruang,0);
			}
		} 

		else if (strcmp(prompt, "LIHAT_USER") == 0 || (strcmp(prompt, "LIHAT_DOKTER") == 0) || (strcmp(prompt, "LIHAT_PASIEN") == 0)) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 1) PilihanLihat(Ulist, prompt);
			else printf("Anda tidak dapat melakukan perintah ini\n");
			
		}
		
		else if (strcmp(prompt, "CARI_USER") == 0 || (strcmp(prompt, "CARI_DOKTER") == 0) || (strcmp(prompt, "CARI_PASIEN") == 0)) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 1) PilihanCari(Ulist, prompt);
			else printf("Anda tidak dapat melakukan perintah ini\n");
		} 
		
		else if (strcmp(prompt, "LIHAT_SEMUA_ANTRIAN") == 0){
			if (loggedIn == 0 ) printf("Anda belum login\n");
			else if ( loggedIn == 1 ) {
				PrintDenah(denah); 
				printf("\n");
				char ruang[5];
				Map ptr;
				ruang[0] = 'A';
				ruang[2] = '\0';

				for (int i = 0; i < denah.M.rows ; i++){
					ruang[1] = '1'; //ASUMSI: MAXLEN RUANG ADALAH 2
					for (int j = 0 ; j < denah.M.cols ; j++) {
						ptr = map_findMap(RuangtoDokter, ruang);
						if (ptr != NULL) {
							PrintRuang(denah, ruang, 1);
							printf("\n");
						}
						ruang[1]++;
					}
					ruang[0]++;
				}
			} else printf("Anda tidak dapat melakukan perintah ini\n");
		}
		
		else if (strcmp(prompt,"TAMBAH_DOKTER") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 1) AddDokter(&Ulist);
			else printf("Anda tidak dapat melakukan perintah ini\n");
		}
		
		else if (strcmp(prompt,"ASSIGN_DOKTER") == 0) {
			if (loggedIn == 0 ) {
				printf("Anda belum login\n");
			}
			else if (loggedIn == 1 ) { 
				AssignDokter() ;
			} else {
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		
		else if (strcmp(prompt,"DIAGNOSIS") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
	
			if (loggedIn == 2) {
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++) {
					if (strcmp(Ulist.contents[i].field[1], user) == 0) {
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				DIAGNOSIS(currentDokter, listRuangan, &Ulist, &Plist);

			} else {
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		} 
		
		else if (strcmp(prompt,"NGOBATIN") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
			if (loggedIn == 2) {
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++) {
					if (strcmp(Ulist.contents[i].field[1], user) == 0) {
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				NGOBATIN(currentDokter, listRuangan, &Ulist, &OPlist);

			} else {
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}

		else if (strcmp(prompt, "PULANGDOK") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 3) pulangdok();
			else printf("Anda tidak dapat melakukan perintah ini\n");
		}
		
		else if (strcmp(prompt,"DAFTAR_CHECKUP") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 3) DaftarCheckup();
			else printf("Anda tidak dapat melakukan perintah ini\n");
		}

		else if (strcmp(prompt,"ANTRIAN") == 0) {
			if (loggedIn == 0) printf("Anda belum login\n");
			else if (loggedIn == 3) CekAntrian(masterID);
			else printf("Anda tidak dapat melakukan perintah ini\n");
		} 

		else if (strcmp(prompt,"MINUM_OBAT") == 0) {
			if (loggedIn == 0) { 
				printf("Anda belum login\n");
			} else if (loggedIn == 3){
				minumObat();
			} else printf("Anda tidak dapat melakukan perintah ini\n");
		} 
		
		else if (strcmp(prompt,"PENAWAR") == 0){
			if (loggedIn == 0){
				printf("Anda belum login\n");
			}  else if (loggedIn == 3){
				minumPenawar();
			} else printf("Anda tidak dapat melakukan perintah ini\n");
		} 
		
		else if (strcmp(prompt, "EXIT") == 0) {
			exitProgram(&exit);
			exit = 1;
		} 

		else if (strcmp(prompt, "SAVE") == 0){
			char folderName[100]; // Panjang nama folder diasumsikan <= 100
			printf("\nMasukkan nama folder: ");
    		scanf("%s", folderName);
			save_all(folderName, &Olist, &OPlist, &Plist, &Ulist);

		}

		/* SPESIFIKASI BONUS*/
		
		else if (strcmp(prompt,"UBAH_DENAH") == 0) {
			if (loggedIn == 0){
				printf("Anda belum login\n");
			} else if (loggedIn == 1) {
				int row,col;
				scanf("%d %d", &row, &col);
				UbahDenah(row,col);
			} else {
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		
		else if (strcmp(prompt,"PINDAH_DOKTER") == 0) { 
			if (loggedIn == 0){
				printf("Anda belum login\n");
			} 
			else if (loggedIn == 1) //melakukan register saat sudah loggedin
			{
				char oldRoom[5], newRoom[5];
				scanf("%s %s", oldRoom, newRoom);
				PindahDokter(oldRoom,newRoom);;
			}
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		
		else if(strcmp(prompt, "SKIP_ANTRIAN") == 0){
			if (loggedIn == 0){
				printf("Anda belum login\n");
			} 
			else if (loggedIn == 3) SkipAntrian();
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		
		else if(strcmp(prompt, "CANCEL_ANTRIAN") == 0){
			if (loggedIn == 0){
				printf("Anda belum login\n");
			} 
			else if (loggedIn == 3) KeluarAntrian();
			else
			{
				printf("Anda tidak dapat melakukan perintah ini\n");
			}
		}
		
		else {
			printf("Perintah tidak valid. Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
		}

	} while (exit == 0);
}

//TODO : update all headers (currently features work fine)

void init() {
	pasienList.neff  = 0;
	managerList.neff = 0;
	dokterList.neff = 0;
	setUser = NULL;
	for(int i = 0 ; i < MAX_USER ; i++){
		linked_create(&USER(Ulist,i).inventoryObat);
		stack_create(&USER(Ulist,i).perut);
		DOKTER(i).antrian = malloc(sizeof(Queue));
		queue_create(DOKTER(i).antrian);
	}
	for(int i = 0 ; i < 100 ; i++){
		for(int j = 0 ; j < 100 ; j++) denah.M.contents[i][j] = -1;
	}
	maxID = 0;
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

void help(loggedIn) {
	printf("\n");
	printf("=========== HELP ===========\n");
	switch (loggedIn) {
	case 0: // loggedIn == 0 -> Belum login
		printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
		printf("    %-48s: %s\n", "1. LOGIN", "Masuk ke dalam akun yang sudah terdaftar");
		printf("    %-48s: %s\n", "2. REGISTER", "Membuat akun baru");
		printf("    %-48s: %s\n", "3. HELP", "Menampilkan daftar perintah yang tersedia");
		printf("    %-48s: %s\n", "4. LUPA_PASSWORD", "Mengubah password akun");
		printf("    %-48s: %s\n", "5. EXIT", "Keluar dari aplikasi\n");
		break;

	case 1: // loggedIn == 1 -> Manager
		printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user);
		printf("    %-48s: %s\n", "1. LOGOUT", "Keluar dari akun yang sedang digunakan");
		printf("    %-48s: %s\n", "2. LUPA_PASSWORD", "Mengubah password akun");
		printf("    %-48s: %s\n", "3. LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
		printf("    %-48s: %s\n", "4. LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
		printf("    %-48s: %s\n", "5. UBAH_DENAH <baris> <kolom>", "Mengubah tampilan denah rumah sakit");
		printf("    %-48s: %s\n", "6. LIHAT_USER", "Melihat daftar user yang terdaftar");
		printf("    %-48s: %s\n", "7. LIHAT_DOKTER", "Melihat daftar dokter yang terdaftar");
		printf("    %-48s: %s\n", "8. LIHAT_PASIEN", "Melihat daftar pasien yang terdaftar");
		printf("    %-48s: %s\n", "9. CARI_USER", "Mencari user berdasarkan ID atau nama");
		printf("    %-48s: %s\n", "10. CARI_DOKTER", "Mencari dokter berdasarkan ID atau nama");
		printf("    %-48s: %s\n", "11. CARI_PASIEN", "Mencari pasien berdasarkan ID, nama, atau penyakit");
		printf("    %-48s: %s\n", "12. LIHAT_SEMUA_ANTRIAN", "Melihat semua antrian yang ada di rumah sakit");
		printf("    %-48s: %s\n", "13. TAMBAH_DOKTER", "Menambahkan dokter baru ke dalam sistem");
		printf("    %-48s: %s\n", "14. ASSIGN_DOKTER", "Menugaskan dokter ke ruangan tertentu");
		printf("    %-48s: %s\n", "15. PINDAH_DOKTER <ruangLama> <ruangBaru>", "Memindahkan dokter dari satu ruangan ke ruangan lain");
		printf("    %-48s: %s\n", "16. EXIT", "Keluar dari aplikasi\n");
		break;

	case 2: // loggedIn == 2 -> Dokter
		printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", user);
		printf("    %-48s: %s\n", "1. LOGOUT", "Keluar dari akun yang sedang digunakan");
		printf("    %-48s: %s\n", "2. LUPA_PASSWORD", "Mengubah password akun");
		printf("    %-48s: %s\n", "3. LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
		printf("    %-48s: %s\n", "4. LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
		printf("    %-48s: %s\n", "5. DIAGNOSIS", "Melakukan diagnosis terhadap pasien");
		printf("    %-48s: %s\n", "6. NGOBATIN", "Memberikan obat kepada pasien");
		printf("    %-48s: %s\n", "7. EXIT", "Keluar dari aplikasi\n");
		break;

	case 3: // loggedIn == 3 -> Pasien
		printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", user);
		printf("    %-48s: %s\n", "1. LOGOUT", "Keluar dari akun yang sedang digunakan");
		printf("    %-48s: %s\n", "2. LUPA_PASSWORD", "Mengubah password akun");
		printf("    %-48s: %s\n", "3. LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
		printf("    %-48s: %s\n", "4. LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
		printf("    %-48s: %s\n", "5. PULANGDOK", "Mengecek status kepulangan pasien (Apakah sudah boleh pulang atau belum?)");
		printf("    %-48s: %s\n", "6. DAFTAR_CHECKUP", "Mendaftarkan diri untuk melakukan checkup");
		printf("    %-48s: %s\n", "7. ANTRIAN", "Melihat posisi antrian pasien saat ini");
		printf("    %-48s: %s\n", "8. MINUM_OBAT", "Meminum obat yang harus diberikan oleh dokter");
		printf("    %-48s: %s\n", "9. PENAWAR", "Meminum penawar untuk mengeluarkan obat terakhir yang diminum dan memasukkannya ke inventory");
		printf("    %-48s: %s\n", "10. SKIP_ANTRIAN", "Melewati antrian dan langsung mendapatkan giliran");
		printf("    %-48s: %s\n", "11. CANCEL_ANTRIAN", "Membatalkan antrian yang sudah didaftarkan");
		printf("    %-48s: %s\n", "12. EXIT", "Keluar dari aplikasi\n");
		break;
	}
	printf("\n");

	printf("Footnote:\n");
	printf("    1. Untuk menggunakan aplikasi, silahkan masukkan perintah yang terdaftar (bukan memasukkan nomor perintah)\n");
	printf("    2. Jangan lupa untuk memasukkan input yang valid\n\n");
}