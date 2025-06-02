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
void help(int loggedIn);
void printWrongRole(int accessLevel);
void printLoggedIn(char* user);
void printNotLoggedIn();
void printNotValid();
void printExit();

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
    int exit = 0, loggedIn = 0;
    
	do {
		printf("\n");
		clearScreen();
		printLogo(); 
		printf("\n");
		printf("=======================================================================================================================\n");
		printf(">>> ");
		scanf("%s", input);
		
		char* prompt = ToUpper(input);
		
		if (strcmp(prompt,"LOGIN") == 0) {
			if (loggedIn != 0) {
				printLoggedIn(user);
        	}
        	else {
				loggedIn = login(Ulist);
        	}
		} 
		
		else if (strcmp(prompt,"REGISTER") == 0) {
			if (loggedIn != 0) {
				printLoggedIn(user);
			}
			else {
				loggedIn = Register(&Ulist);
			}
			
		} 
		
		else if (strcmp(prompt,"LOGOUT") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
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
				printNotLoggedIn();
			}
			else {
				PrintDenah(denah);
			}
		} 
		
		else if (strcmp(prompt,"LIHAT_RUANGAN") == 0) {
			if (loggedIn == 0) {
				printNotLoggedIn();
			}
			else {
				char ruang[5]; //ASUMSI : ruang hanya menggunakan 2 char
    			scanf("%s", ruang);
				PrintRuang(denah,ruang,0);
			}
		} 

		else if (strcmp(prompt, "LIHAT_USER") == 0 || (strcmp(prompt, "LIHAT_DOKTER") == 0) || (strcmp(prompt, "LIHAT_PASIEN") == 0)) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) PilihanLihat(Ulist, prompt);
			else printWrongRole(1);
			
		}
		
		else if (strcmp(prompt, "CARI_USER") == 0 || (strcmp(prompt, "CARI_DOKTER") == 0) || (strcmp(prompt, "CARI_PASIEN") == 0)) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) PilihanCari(Ulist, prompt);
			else printWrongRole(1);
		} 
		
		else if (strcmp(prompt, "LIHAT_SEMUA_ANTRIAN") == 0){
			if (loggedIn == 0 ) printNotLoggedIn();
			else if (loggedIn == 1) {
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
			} else printWrongRole(1);
		}
		
		else if (strcmp(prompt,"TAMBAH_DOKTER") == 0) { 
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) AddDokter(&Ulist);
			else printWrongRole(1);
		}
		
		else if (strcmp(prompt,"ASSIGN_DOKTER") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) AssignDokter();
			else printWrongRole(1);
		}
		
		else if (strcmp(prompt,"DIAGNOSIS") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 2) {
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++) {
					if (strcmp(Ulist.contents[i].field[1], user) == 0) {
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				DIAGNOSIS(currentDokter, listRuangan, &Ulist, &Plist);
			} else printWrongRole(2);
		} 
		
		else if (strcmp(prompt,"NGOBATIN") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			if (loggedIn == 2) {
				User currentDokter;
				for (int i = 0; i < Ulist.len; i++) {
					if (strcmp(Ulist.contents[i].field[1], user) == 0) {
						currentDokter = Ulist.contents[i];
						break;
					}
				}
				NGOBATIN(currentDokter, listRuangan, &Ulist, &OPlist);

			} else printWrongRole(2);
		}

		else if (strcmp(prompt, "PULANGDOK") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) pulangdok();
			else printWrongRole(3);
		}
		
		else if (strcmp(prompt,"DAFTAR_CHECKUP") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) DaftarCheckup();
			else printWrongRole(3);
		}

		else if (strcmp(prompt,"ANTRIAN") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) CekAntrian(masterID);
			else printWrongRole(3);
		} 

		else if (strcmp(prompt,"MINUM_OBAT") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) minumObat();
			else printWrongRole(3);
		} 
		
		else if (strcmp(prompt,"PENAWAR") == 0){
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) minumPenawar();
			else printWrongRole(3);
		} 
		
		else if (strcmp(prompt, "EXIT") == 0) {
			int save = exitProgram();
			
			if (save == 1) {
				char folderName[100]; // Panjang nama folder diasumsikan <= 100
				printf("\nMasukkan nama folder: ");
				scanf("%s", folderName);
				save_all(folderName, &Olist, &OPlist, &Plist, &Ulist);
			}
			
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
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) {
				int row,col;
				scanf("%d %d", &row, &col);
				UbahDenah(row,col);
			} else printWrongRole(1);
		}
		
		else if (strcmp(prompt,"PINDAH_DOKTER") == 0) { 
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) {
				char oldRoom[5], newRoom[5];
				scanf("%s %s", oldRoom, newRoom);
				PindahDokter(oldRoom,newRoom);;
			} else printWrongRole(1);
		}
		
		else if (strcmp(prompt, "SKIP_ANTRIAN") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) SkipAntrian();
			else printWrongRole(3);
		}
		
		else if (strcmp(prompt, "CANCEL_ANTRIAN") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3) KeluarAntrian();
			else printWrongRole(3);
		}

		else if (strcmp(prompt, "GACHA_GAMING") == 0) {
			if (loggedIn == 0) printNotLoggedIn(); 
			else if (loggedIn == 3) Gacha();
			else printWrongRole(3);
		}

		else if (strcmp(prompt, "LIHAT_DOMPET") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 3 || loggedIn == 2) LihatDompet();
			else printWrongRole(4);
		}

		else if (strcmp(prompt, "LIHAT_FINANSIAL") == 0) {
			if (loggedIn == 0) printNotLoggedIn();
			else if (loggedIn == 1) LihatFinansial();
			else printWrongRole(1);
		}

		else {
			printNotValid();
		}

		waitEnter();
	} while (exit == 0);
	printExit();
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


void help(int loggedIn) {
	printf("\n");
	printf("========================================================   HELP   ========================================================\n");
	switch (loggedIn) {
		case 0: // loggedIn == 0 -> Belum login
			printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n");
			printf("%2s. %-44s: %s\n", "1", "LOGIN", "Masuk ke dalam akun yang sudah terdaftar");
			printf("%2s. %-44s: %s\n", "2", "REGISTER", "Membuat akun baru");
			printf("%2s. %-44s: %s\n", "3", "HELP", "Menampilkan daftar perintah yang tersedia");
			printf("%2s. %-44s: %s\n", "4", "LUPA_PASSWORD", "Mengubah password akun");
			printf("%2s. %-44s: %s\n", "5", "EXIT", "Keluar dari aplikasi\n");
			break;
		
		case 1: // loggedIn == 1 -> Manager
			printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user);
			printf("%2s. %-44s: %s\n", "1", "LOGOUT", "Keluar dari akun yang sedang digunakan");
			printf("%2s. %-44s: %s\n", "2", "LUPA_PASSWORD", "Mengubah password akun");
			printf("%2s. %-44s: %s\n", "3", "LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
			printf("%2s. %-44s: %s\n", "4", "LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
			printf("%2s. %-44s: %s\n", "5", "UBAH_DENAH <baris> <kolom>", "Mengubah tampilan denah rumah sakit");
			printf("%2s. %-44s: %s\n", "6", "LIHAT_USER", "Melihat daftar user yang terdaftar");
			printf("%2s. %-44s: %s\n", "7", "LIHAT_DOKTER", "Melihat daftar dokter yang terdaftar");
			printf("%2s. %-44s: %s\n", "8", "LIHAT_PASIEN", "Melihat daftar pasien yang terdaftar");
			printf("%2s. %-44s: %s\n", "9", "CARI_USER", "Mencari user berdasarkan ID atau nama");
			printf("%2s. %-44s: %s\n", "10", "CARI_DOKTER", "Mencari dokter berdasarkan ID atau nama");
			printf("%2s. %-44s: %s\n", "11", "CARI_PASIEN", "Mencari pasien berdasarkan ID, nama, atau penyakit");
			printf("%2s. %-44s: %s\n", "12", "LIHAT_SEMUA_ANTRIAN", "Melihat semua antrian yang ada di rumah sakit");
			printf("%2s. %-44s: %s\n", "13", "TAMBAH_DOKTER", "Menambahkan dokter baru ke dalam sistem");
			printf("%2s. %-44s: %s\n", "14", "ASSIGN_DOKTER", "Menugaskan dokter ke ruangan tertentu");
			printf("%2s. %-44s: %s\n", "15", "PINDAH_DOKTER <ruangLama> <ruangBaru>", "Memindahkan dokter dari satu ruangan ke ruangan lain");
			printf("%2s. %-44s: %s\n", "16", "LIHAT_FINANSIAL", "Melihat laporan keuangan rumah sakit");
			printf("%2s. %-44s: %s\n", "17", "EXIT", "Keluar dari aplikasi\n");
			break;
		
		case 2: // loggedIn == 2 -> Dokter
			printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user);
			printf("%2s. %-44s: %s\n", "1", "LOGOUT", "Keluar dari akun yang sedang digunakan");
			printf("%2s. %-44s: %s\n", "2", "LUPA_PASSWORD", "Mengubah password akun");
			printf("%2s. %-44s: %s\n", "3", "LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
			printf("%2s. %-44s: %s\n", "4", "LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
			printf("%2s. %-44s: %s\n", "5", "DIAGNOSIS", "Melakukan diagnosis terhadap pasien");
			printf("%2s. %-44s: %s\n", "6", "NGOBATIN", "Memberikan obat kepada pasien");
			printf("%2s. %-44s: %s\n", "8", "LIHAT_DOMPET", "Melihat isi dompet dokter");
			printf("%2s. %-44s: %s\n", "9", "EXIT", "Keluar dari aplikasi\n");
			break;
		
		case 3: // loggedIn == 3 -> Pasien
			printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n", user);
			printf("%2s. %-44s: %s\n", "1", "LOGOUT", "Keluar dari akun yang sedang digunakan");
			printf("%2s. %-44s: %s\n", "2", "LUPA_PASSWORD", "Mengubah password akun");
			printf("%2s. %-44s: %s\n", "3", "LIHAT_DENAH", "Menampilkan denah berisikan ruangan-ruangan yang ada di rumah sakit");
			printf("%2s. %-44s: %s\n", "4", "LIHAT_RUANGAN <nomorRuangan>", "Menampilkan detail suatu ruangan");
			printf("%2s. %-44s: %s\n", "5", "PULANGDOK", "Mengecek status kepulangan pasien (Apakah sudah boleh pulang atau belum?)");
			printf("%2s. %-44s: %s\n", "6", "DAFTAR_CHECKUP", "Mendaftarkan diri untuk melakukan checkup");
			printf("%2s. %-44s: %s\n", "7", "ANTRIAN", "Melihat posisi antrian pasien saat ini");
			printf("%2s. %-44s: %s\n", "8", "MINUM_OBAT", "Meminum obat yang harus diberikan oleh dokter");
			printf("%2s. %-44s: %s\n", "9", "PENAWAR", "Meminum penawar untuk mengeluarkan obat terakhir yang diminum dan memasukkannya ke inventory");
			printf("%2s. %-44s: %s\n", "10", "SKIP_ANTRIAN", "Melewati antrian dan langsung mendapatkan giliran");
			printf("%2s. %-44s: %s\n", "11", "CANCEL_ANTRIAN", "Membatalkan antrian yang sudah didaftarkan");
			printf("%2s. %-44s: %s\n", "12", "GACHA_GAMING", "Melakukan gacha untuk mendapatkan banarich tambahan");
			printf("%2s. %-44s: %s\n", "13", "LIHAT_DOMPET", "Melihat isi dompet pasien");
			printf("%2s. %-44s: %s\n", "14", "EXIT", "Keluar dari aplikasi\n");
			break;
	}
	printf("\n");
	
	printf("Footnote:\n");
	printf("    1. Untuk menggunakan aplikasi, silahkan masukkan perintah yang terdaftar (bukan memasukkan nomor perintah)\n");
	printf("    2. Jangan lupa untuk memasukkan input yang valid\n\n");
} 

// ASCII ART

void printLogo() {
    printf("\033[0;33m%-103s\033[0m\n", "=====================================================================================================");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⠀⠀⠀⠀⢀⣴⠾⠛⠉⠉⠉⠉⠛⠿⣦⡀⠀    ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⠀⠀⠀⢠⡿⠁⠀⢀⣠⣤⣤⣄⡀⠀⠈⢿⡆    ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⠀⠀⢀⣿⣁⣀⣠⡿⠋⠀⠀⠙⢿⣄⣀⣈⣿⡀   ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██████  ███████     ███    ██ ██ ███    ███  ██████  ███    ██ ███████  ", " ⠀⠀⢸⣿⠛⠛⢻⣧⠀⠿⠇⠀⣼⡟⠛⠛⣿⡇   ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██   ██ ██          ████   ██ ██ ████  ████ ██    ██ ████   ██ ██       ", "⠀⠀ ⢸⣿⠀⠀⠀⠙⢷⣦⣴⡾⠋⠀⠀ ⣿⡇   ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██   ██ ██          ████   ██ ██ ████  ████ ██    ██ ████   ██ ██       ", " ⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⣿⡇   ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██████  ███████     ██ ██  ██ ██ ██ ████ ██ ██    ██ ██ ██  ██ ███████  ", " ⠀⠀⣸⣿⠀⠀⠀⠛⠷⠶⠶⠾⠛⠀⠀ ⣿⣇   ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██   ██      ██     ██  ██ ██ ██ ██  ██  ██ ██    ██ ██  ██ ██      ██  ", " ⠀⣸⣿⣿⢷⣦⣀⣀⣀⣀⣀⣀⣀⣀⣴⡾⣿⣿⣇⠀ ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██   ██      ██     ██  ██ ██ ██ ██  ██  ██ ██    ██ ██  ██ ██      ██  ", " ⢠⣿⢸⣿⠀⣿⡏⠉⠉⠉⠉⠉⠉⢹⣿⠀⣿⡇⣿⡄ ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "██   ██ ███████     ██   ████ ██ ██      ██  ██████  ██   ████ ███████  ", " ⢸⡏⢸⣿⣀⣿⡇⠀⠀⠀⠀⠀⠀⢸⣿⣀⣿⡇⢹⡇ ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⢸⡇⠀⢿⣏⠉⠁⠀⠀⠀⠀⠀⠀ ⠈⠉⣹⡿⠀⢸⡇");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⢸⣿⣤⣌⠛⠷⣶⣶⣶⣶⣶⣶⣶⣶⠾⠛⣡⣤⣿⡇ ");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⠘⠿⠿⠇⠀⠀⠀⢿⡾⠇ ⠸⢷⡿⠀⠀⠀⠸⠿⠿⠃");
    printf("\033[0;33m|| %-72s %37s ||\033[0m\n", "", " ⠀⠀⠀⠀⠀⠀⠀⠛⠛⠁ ⠈⠛⠛⠀⠀⠀⠀⠀⠀⠀");
    printf("\033[0;33m%-103s\033[0m\n", "=====================================================================================================");

    printf("Selamat datang di aplikasi Rumah Sakit Nimons!\n");
    printf("Silahkan masukkan perintah yang diinginkan.\n");
    printf("Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
}

void printWrongRole(int accessLevel) {
	usleep(0250 * 1000);
	printf(" _______    ___   _________   ________           _________   ___   ________   ________   ___  __            ________   ___   ________   ________       \n");
	printf("|\\  ___ \\  |\\  \\ |\\___   ___\\|\\   ____\\         |\\___   ___\\|\\  \\ |\\   ___ \\ |\\   __  \\ |\\  \\|\\  \\         |\\   __  \\ |\\  \\ |\\   ____\\ |\\   __  \\      \n");
	printf("\\ \\   __/| \\ \\  \\\\|___ \\  \\_|\\ \\  \\___|_        \\|___ \\  \\_|\\ \\  \\\\ \\  \\_|\\ \\\\ \\  \\|\\  \\\\ \\  \\/  /|_       \\ \\  \\|\\ /_\\ \\  \\\\ \\  \\___|_\\ \\  \\|\\  \\     \n");
	printf(" \\ \\  \\_|/__\\ \\  \\    \\ \\  \\  \\ \\_____  \\            \\ \\  \\  \\ \\  \\\\ \\  \\ \\\\ \\\\ \\   __  \\\\ \\   ___  \\       \\ \\   __  \\\\ \\  \\\\ \\_____  \\\\ \\   __  \\    \n");
	printf("  \\ \\  \\_|\\ \\\\ \\  \\    \\ \\  \\  \\|____|\\  \\            \\ \\  \\  \\ \\  \\\\ \\  \\_\\\\ \\\\ \\  \\ \\  \\\\ \\  \\\\ \\  \\       \\ \\  \\|\\  \\\\ \\  \\\\|____|\\  \\\\ \\  \\ \\  \\   \n");
	printf("    \\|_______| \\|__|     \\|__| |\\_________\\            \\|__|   \\|__| \\|_______| \\|__|\\|__| \\|__| \\|__|        \\|_______| \\|__||\\_________\\\\|__|\\|__|  \n");
	printf("                               \\|_________|                                                                                   \\|_________|             \n");
	printf("\n");
	
	printf("\033[1mAnda tidak memiliki akses\033[0m untuk melakukan perintah ini\n");
	printf("Silakan login sebagai \033[1m%s\033[0m untuk mengakses perintah ini\n", accessLevel == 1 ? "Manager" : accessLevel == 2 ? "Dokter" : accessLevel == 3 ? "Pasien" : accessLevel == 4 ? "Dokter atau Pasien" : "pengguna lain");
	printf("Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");

}

void printLoggedIn(char* user) {
	usleep(250 * 1000);
	printf("                  _         _       _                _             _         _      _ \n");
	printf("                 | |       | |     | |              (_)           | |       | |    | |\n");
	printf("  ___  _   _   __| |  __ _ | |__   | |  ___    __ _  _  _ __      | |  ___  | |__  | |\n");
	printf(" / __|| | | | / _` | / _` || '_ \\  | | / _ \\  / _` || || '_ \\     | | / _ \\ | '_ \\ | |\n");
	printf(" \\__ \\| |_| || (_| || (_| || | | | | || (_) || (_| || || | | | _  | || (_) || | | ||_|\n");
	printf(" |___/ \\__,_| \\__,_| \\__,_||_| |_| |_| \\___/  \\__, ||_||_| |_|( ) |_| \\___/ |_| |_|(_)\n");
	printf("                                               __/ |          |/                      \n");
	printf("                                              |___/                                   \n");
	printf("\n");

	printf("\033[1mAnda sudah login\033[0m sebagai \033[1m%s\033[0m\n", user);
	printf("Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
	printf("Ketik 'LOGOUT' untuk keluar dari akun yang sedang digunakan.\n");
}

void printNotLoggedIn() {     
	usleep(250 * 1000);
	printf("  _            _                     _                _             _         _      _ \n");
	printf(" | |          | |                   | |              (_)           | |       | |    | |\n");
	printf(" | |__    ___ | | _   _  _ __ ___   | |  ___    __ _  _  _ __      | |  ___  | |__  | |\n");
	printf(" | '_ \\  / _ \\| || | | || '_ ` _ \\  | | / _ \\  / _` || || '_ \\     | | / _ \\ | '_ \\ | |\n");
	printf(" | |_) ||  __/| || |_| || | | | | | | || (_) || (_| || || | | | _  | || (_) || | | ||_|\n");
	printf(" |_.__/  \\___||_| \\__,_||_| |_| |_| |_| \\___/  \\__, ||_||_| |_|( ) |_| \\___/ |_| |_|(_)\n");
	printf("                                               __/ |          |/                      \n");
	printf("                                              |___/                                   \n");
	printf("\n");

	printf("\033[1mAnda belum login\033[0m, harap melakukan login atau register terlebih dahulu\n");
	printf("Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
}

void printNotValid() {
	usleep(250 * 1000);
	printf(" ▄· ▄▌ ▐ ▄ ▄▄▄▄▄▄ •▄ ▄▄▄▄▄.▄▄ ·\n");
	printf("▐█▪██▌•█▌▐█•██  █▌▄▌▪•██  ▐█ ▀. \n");
	printf("▐█▪██▌•█▌▐█•██  █▌▄▌▪•██  ▐█ ▀.\n");
	printf("▐█▌▐█▪▐█▐▐▌ ▐█.▪▐▀▀▄· ▐█.▪▄▀▀▀█▄\n");
	printf(" ▐█▀·.██▐█▌ ▐█▌·▐█.█▌ ▐█▌·▐█▄▪▐█\n");
	printf("  ▀ • ▀▀ █▪ ▀▀▀ ·▀  ▀ ▀▀▀  ▀▀▀▀ ▀▀\n");
	printf("YA NDAK TAU KOK TANYA SAYA!!\n");

	printf("\033[1mPerintah tidak valid\033[0m]. Ketik 'HELP' untuk melihat daftar perintah yang tersedia.\n");
}

void printExit() {
    usleep(250 * 1000);
    
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⣿⠿⠗⠚⠛⠋⠉⠉⠛⠛⠻⣿⡷⠾⠛⠛⠻⠶⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣼⣿⡿⠛⠉⠀⠀⣠⡤⠶⠒⠶⣤⣀⢀⡴⠉⣠⣶⣿⠿⣯⣕⠢⣌⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠋⠀⠀⠀⣠⠊⢁⣴⣶⣶⣶⡶⣌⠙⠀⢰⠋⠀⠀⠀⠀⠈⠳⣝⡆⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡿⠋⠀⠀⠀⠀⣴⠃⣴⠋⠁⠀⠀⠀⠙⢪⣳⡄⢸⡀⣠⣤⣄⠀⠀⠀⢹⣡⠀⡇⠀⠀⠀⠀⠀⠀⠀⡞⣿⣻⠀⢀⣀⡀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⣴⡶⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠁⠀⠀⠀⢠⣾⣯⠀⣿⠀⠀⣀⣤⣄⠀⠀⢻⡇⠀⢳⣿⣿⣿⡇⠀⠀⣸⠇⣼⠁⠀⠀⠀⢀⣤⣶⡞⠳⣬⣿⣤⡟⠉⣿⣄\033[0m\n");
    printf("\033[0;33m⠀⢀⣹⡄⠘⠳⠿⠿⠦⠤⢤⣤⣄⠀⠀⠀⠀⢰⡇⠀⠀⢀⡴⢿⣿⣿⡄⠙⣄⠀⣿⣿⣿⡇⠀⣸⠇⣠⣄⡈⠛⠫⠤⠤⠞⣁⡼⠃⠀⠀⠀⣠⠞⠻⣦⣦⢤⣀⠀⢀⣀⡴⢏⡿\033[0m\n");
    printf("\033[0;33m⠠⡾⠉⠻⢦⠀⠀⠀⠀⣶⣾⠏⠛⢦⣄⠀⠀⢸⠀⢀⡔⣋⡴⠛⣯⣿⣟⣦⡈⠓⢬⣿⣭⣤⡴⠋⣠⠿⣿⡿⣷⣶⣶⣶⠟⠋⣽⠀⠀⢠⠞⠁⢀⡾⠛⠋⠀⠉⠉⠉⠓⠚⠉⠁\033[0m\n");
    printf("\033[0;33m⠀⠙⠦⠤⠾⠶⠶⠖⠋⠙⠿⠲⢤⡀⠈⠳⣦⣸⡷⣫⠞⢁⡴⠞⠉⠉⠻⣿⣏⣳⣶⣤⣤⣴⠶⠛⠁⠀⠀⠉⠉⠉⠉⠀⠀⠀⢹⡇⣰⠃⠀⣰⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠷⣄⠈⠛⢿⣤⣖⡁⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡀⢰⣷⠃⠀⡼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢷⡀⠀⠙⢯⡉⠛⢶⣄⠀⠀⠀⠀⠀⠀⠀⣤⠤⠴⠦⠤⠤⣀⣤⠤⠴⣖⣉⡵⡇⠈⢻⣆⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡄⠀⠀⠙⢷⣄⡘⢷⡄⠀⠀⠀⠀⠀⢷⡜⠷⣦⡤⠤⠟⠲⣞⠋⠁⠀⢠⡇⠀⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀⠀⠀⠙⣷⠂⠙⣦⠀⠀⠀⠀⠈⠳⣄⠀⠉⠀⠀⠀⣿⢀⣀⣠⠞⠀⢠⡏⢿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠈⢷⣄⠈⢷⣄⠀⠀⠀⠀⠈⠙⠲⠿⠭⠭⠭⠽⠛⠁⠀⢀⣾⡅⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡇⠀⠀⠀⠀⠈⢻⣶⠀⢻⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⢿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⢻⣷⣿⣿⡿⢿⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠂⢿⣿⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠀⠀⠈⡿⣿⡿⠁⠀⠈⠻⢷⣦⡤⣄⣀⣤⢤⡾⠏⠁⠀⠀⣿⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⣿⠈⠁⠀⠀⠀⠀⠀⠈⠉⠙⠛⠙⠉⠀⠀⠀⠀⠀⣿⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⣿⠃⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀⢀⣴⣧⠀⠀⠀⡟⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣧⣀⠀⠀⠀⠀⢀⣿⡄⠀⠀⠀⠀⢸⡏⠽⣖⣒⣲⣾⡝⠉⣿⡄⠀⠠⡧⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠘⠿⠯⢗⢒⣒⣻⠃⠀⠀⠀⢀⢸⡇⠀⣠⣿⡿⣷⣦⠀⣿⡇⠀⠸⣿⡾⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢽⡇⠀⠀⠀⠀⠀⣶⡇⠀⠀⠀⠀⠘⣸⡇⠀⣿⢳⣶⣬⢿⣿⣿⡇⠀⢰⡆⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⠀⠀⠀⣰⡟⠀⠀⠀⠀⠀⠀⠹⣿⠀⢿⣧⣝⣣⣿⢏⡿⠁⠀⢸⣇⢀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣷⠀⢠⣠⡼⠟⠀⠀⠀⠀⠀⠀⠀⠀⠻⣷⡀⡉⢛⣋⣥⡾⠃⠀⠀⠈⢻⣼⣇⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⢻⣆⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠋⠉⠁⠀⠀⠀⣠⣴⣿⡿⠉⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⠃⡼⠙⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡤⢖⡻⢾⣿⡿⠀⢰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣿⣁⣀⣷⡀⠈⠙⢢⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠤⠔⠒⠛⠉⢣⣠⠎⣠⣾⠛⣳⠶⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠀⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⡿⢉⡽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
    printf("\033[0;33m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣙⠋⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");

    printf("\nSampai jumpa lagi di aplikasi Rumah Sakit Nimons!\n");
    printf("Terima kasih telah menggunakan layanan kami.\n");
}

void clearScreen() {
    printf("\033[2J\033[H");
}

void waitEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    while (getchar() != '\n');
    getchar();
}