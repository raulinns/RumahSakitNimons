#include "../header/exit.h"
int exitProgram() {
	char prompt[10]; // Menyimpan input pengguna
	int valid = 0;
	int choice;
	do {
		printf("Apakah Anda yakin ingin keluar? (y/n): ");
		scanf("%s", prompt);
		if (strcmp(prompt, "y") == 0 || strcmp(prompt, "Y") == 0 || strcmp(prompt, "yes") == 0 || strcmp(prompt, "YES") == 0 || strcmp(prompt, "YA") == 0 || strcmp(prompt, "ya") == 0) {
			choice = 1; // Pilihan 1 untuk keluar
			valid = 1; // Menyatakan input valid
		} else if (strcmp(prompt, "n") == 0 || strcmp(prompt, "N") == 0 || strcmp(prompt, "no") == 0 || strcmp(prompt, "NO") == 0 || strcmp(prompt, "TIDAK") == 0 || strcmp(prompt, "tidak") == 0) {
			printf("Kembali ke menu utama.\n");
			choice = 2; // Pilihan 2 untuk kembali ke menu utama
			valid = 1; // Menyatakan input valid
		} else {
			printf("Masukan tidak valid. Silakan coba lagi.\n");
			valid = 0; 
		}
	} while (!valid);

	if (choice == 1) {
		printf("Apakah anda mau melakukan penyimpanan file yang sudah diubah? (y/n): ");
		scanf("%s", prompt);
		if (strcmp(prompt, "y") == 0 || strcmp(prompt, "Y") == 0 || strcmp(prompt, "yes") == 0 || strcmp(prompt, "YES") == 0 || strcmp(prompt, "YA") == 0 || strcmp(prompt, "ya") == 0) {
			return 1;
		} else if (strcmp(prompt, "n") == 0 || strcmp(prompt, "N") == 0 || strcmp(prompt, "no") == 0 || strcmp(prompt, "NO") == 0 || strcmp(prompt, "TIDAK") == 0 || strcmp(prompt, "tidak") == 0) {
			printf("Data tidak disimpan.\n");
			return 0;
		}

	} else if (choice == 2) {
		return 0;
	}
}

void saveFile(Set *userSet) { // Tambahkan parameter sendiri kalau mau save file, tinggal copy 2 line yang gw hightlight
	FILE *writeFile = fopen("file/user.csv", "w");
	if (writeFile != NULL) {
		Set maxCapacity[1000];
		int top = -1;

		Set current = *userSet;
		int status = 0;

		while (!status) {
			if (current != NULL) {
				maxCapacity[++top] = current;
				current = current->l;
			} else {
				if (top == -1) {
					status = 1;
				} else {
					current = maxCapacity[top--];
					fprintf(writeFile, "%d;;;;;;;;;;;;;;;\n", current->key);
					current = current->r;
				}
			}
		}
	}
	fclose(writeFile);
	printf("Data telah disimpan.\n");
}