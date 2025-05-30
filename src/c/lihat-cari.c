#include "lihat-cari.h"

char* ToLower (char *str) {
	char* lowerstr = (char*)malloc(strlen(str) + 1);
	strcpy(lowerstr, str);

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			lowerstr[i] = str[i] + 32;
		}
	}
	return lowerstr;
}

char* ToUpper (char *str) {
	char* upperstr = (char*)malloc(strlen(str) + 1);
	strcpy(upperstr, str);
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			upperstr[i] = str[i] - 32;
		}
	}
	return upperstr;
}

UserList sortList (UserList uList, int urutan, int sort) {
	UserList sortedList;
	length(sortedList) = 0;

	for (int i = 0; i < length(uList); i++) {
		sortedList.contents[i] = uList.contents[i];
		length(sortedList)++;
	}

	for (int i = 0; i < length(sortedList) - 1; i++) {
		for (int j = 0; j < length(sortedList) - i - 1; j++) {
			if (urutan == 1) {
				if (sort == 1) {
					if (atoi(id(sortedList.contents[j])) > atoi(id(sortedList.contents[j + 1]))) {
						User temp = sortedList.contents[j];
						sortedList.contents[j] = sortedList.contents[j + 1];
						sortedList.contents[j + 1] = temp;
					}
				} else if (sort == 2) {
					if (atoi(id(sortedList.contents[j])) < atoi(id(sortedList.contents[j + 1]))) {
						User temp = sortedList.contents[j];
						sortedList.contents[j] = sortedList.contents[j + 1];
						sortedList.contents[j + 1] = temp;
					}
				}
			} else if (urutan == 2) {
				char* lowerCurrent = ToLower(username(sortedList.contents[j]));
				char* lowerNext = ToLower(username(sortedList.contents[j + 1]));

				if (sort == 1) {
					if (strcmp(lowerCurrent, lowerNext) > 0) {
						User temp = sortedList.contents[j];
						sortedList.contents[j] = sortedList.contents[j + 1];
						sortedList.contents[j + 1] = temp;
					}
				} else if (sort == 2) {
					if (strcmp(lowerCurrent, lowerNext) < 0) {
						User temp = sortedList.contents[j];
						sortedList.contents[j] = sortedList.contents[j + 1];
						sortedList.contents[j + 1] = temp;
					}
				}

				free(lowerCurrent);
				free(lowerNext);
			}
		}
	}

	return sortedList;
}

void PilihanLihat (UserList uList, char *prompt) {
	if (strcmp(prompt, "LIHAT_USER") == 0) {
		LihatUser(uList, 1);
	} else if (strcmp(prompt, "LIHAT_PASIEN") == 0) {
		LihatPasien(uList);
	} else if (strcmp(prompt, "LIHAT_DOKTER") == 0) {
		LihatDokter(uList);
	}
}

void MenuLihat (int *urutan, int *sort, char *urutanLihat, char *sortLihat) {
	printf("Basis pengurutan: \n");
	printf("1. ID\n");
	printf("2. Nama\n");
	do {
		printf(">>> Pilihan: ");
		scanf("%d", urutan);
		if (*urutan != 1 && *urutan != 2) printf("Pilihan tidak valid\n");
	} while (*urutan != 1 && *urutan != 2);

	
	if (*urutan == 1) strcpy(urutanLihat, "ID");
	else if (*urutan == 2) strcpy(urutanLihat, "Nama");

	printf("\n");
	printf("Metode pengurutan: \n");
	printf("1. ASC (A-Z)\n");
	printf("2. DESC (Z-A)\n");
	do {
		printf(">>> Pilihan: ");
		scanf("%d", sort);
		if (*sort != 1 && *sort != 2) printf("Pilihan tidak valid\n");
	} while (*sort != 1 && *sort != 2);

	if (*sort == 1) strcpy(sortLihat, "ascending");
	else if (*sort == 2) strcpy(sortLihat, "descending");
}

void LihatUser (UserList uList, int pilihan) {
	int urutan, sort;
	char urutanLihat[5], sortLihat[11];

	MenuLihat(&urutan, &sort, urutanLihat, sortLihat);
	UserList sortedList = sortList(uList, urutan, sort);
	
	printf("\n");
	printf("Menampilkan semua pengguna dengan %s terurut %s...\n", urutanLihat, sortLihat);

	if (pilihan == 1) {
		printf("-------------------------------------------------\n");
		printf("|-ID-|-----Nama-----|---Role---|----Penyakit----|\n");
		printf("-------------------------------------------------\n");
		
		for (int i = 0; i < length(sortedList); i++) {
			if ((strcmp(role(sortedList.contents[i]), "Dokter") == 0) || (strcmp(role(sortedList.contents[i]), "Manager") == 0)) {
				printf("| %.2d | %-12s | %-8s |       -        |\n", atoi(id(sortedList.contents[i])), username(sortedList.contents[i]), role(sortedList.contents[i]));
			} else {
				printf("| %.2d | %-12s | %-8s | %-14s |\n", atoi(id(sortedList.contents[i])), username(sortedList.contents[i]), role(sortedList.contents[i]), riwayat(sortedList.contents[i]));
			}
		}
		printf("-------------------------------------------------\n");
	} else if (pilihan == 2) {
		printf("--------------------------------------\n");
		printf("|-ID-|-----Nama-----|----Penyakit----|\n");
		printf("--------------------------------------\n");

		for (int i = 0; i < length(sortedList); i++) {
			if (strcmp(role(sortedList.contents[i]), "Pasien") == 0) {
				printf("| %.2d | %-12s | %-14s |\n", atoi(id(sortedList.contents[i])), username(sortedList.contents[i]), riwayat(sortedList.contents[i]));
			}
		}
        printf("--------------------------------------\n");
	} else if (pilihan == 3) {
		printf("---------------------\n");
		printf("|-ID-|-----Nama-----|\n");
		printf("---------------------\n");

		for (int i = 0; i < length(sortedList); i++) {
			if (strcmp(role(sortedList.contents[i]), "Dokter") == 0) {
				printf("| %.2d | %-12s |\n", atoi(id(sortedList.contents[i])), username(sortedList.contents[i]));
			}
		}
        printf("---------------------\n");
	}
}

void LihatPasien (UserList uList) {
	UserList pasienList;
	length(pasienList) = 0;

	for (int i = 0; i < length(uList); i++) {
		if (strcmp(role(uList.contents[i]), "Pasien") == 0) {
			pasienList.contents[pasienList.len] = uList.contents[i];
			length(pasienList)++;
		}
	}

	LihatUser(pasienList, 2);
}

void LihatDokter (UserList uList) {
	UserList dokterList;
	length(dokterList) = 0;

	for (int i = 0; i < length(uList); i++) {
		if (strcmp(role(uList.contents[i]), "Dokter") == 0) {
			dokterList.contents[dokterList.len] = uList.contents[i];
			length(dokterList)++;
		}
	}

	LihatUser(dokterList, 3);
}

void BinarySearchUser(UserList uList, int id, int first, int last, UserList *hasilCari) {
    if (first <= last) {
        int mid = first + (last - first) / 2;
        int currentId = atoi(id(uList.contents[mid]));

        if (currentId == id) {
            hasilCari->contents[0] = uList.contents[mid];
            length(*hasilCari)++;
        } else if (currentId < id) {
            BinarySearchUser(uList, id, mid + 1, last, hasilCari);
        } else {
            BinarySearchUser(uList, id, first, mid - 1, hasilCari);
        }
    }
}

void PilihanCari (UserList uList, char* prompt) {
    if (strcmp(prompt, "CARI_USER") == 0) {
        CariUser(uList, 1);
    } else if (strcmp(prompt, "CARI_PASIEN") == 0) {
        CariPasien(uList);
    } else if (strcmp(prompt, "CARI_DOKTER") == 0) {
        CariDokter(uList);
    }
}

void MenuCari (int *basis, char *basisCari, char *data, int pilihan) {
    printf("Basis Pencarian: \n");
    printf("1. ID\n");
    printf("2. Nama\n");
    if (pilihan == 2) {
        printf("3. Penyakit\n");
    }

    do {
        printf(">>> Pilihan: ");
        scanf("%d", basis);
        if (*basis != 1 && *basis != 2 && *basis != 3) printf("Pilihan tidak valid\n");
    } while (*basis != 1 && *basis != 2 && *basis != 3);

    if (*basis == 1) strcpy(basisCari, "nomor ID");
    else if (*basis == 2) strcpy(basisCari, "nama");
    else if (*basis == 3) strcpy(basisCari, "penyakit");

    if (*basis == 1 || *basis == 2) {
        printf(">>> Masukkan %s user: ", basisCari);
        scanf("%s", data);
    } else if (*basis == 3) {
        printf(">>> Masukkan nama %s: ", basisCari);
        scanf("%s", data);
    }
}

void CariUser (UserList uList, int pilihan) {
    int basis;
    char basisCari[20], data[MAX_FIELD_LENGTH];

    MenuCari(&basis, basisCari, data, pilihan);
    
    UserList sortedList = sortList(uList, 1, 1);
    length(sortedList) = length(uList);

    UserList hasilCari;
    length(hasilCari) = 0;

    if (basis == 1) {
        int id = atoi(data);
        BinarySearchUser(sortedList, id, 0, length(uList) - 1, &hasilCari);

    } else if (basis == 2) {
        char* lowerData = ToLower(data);
        for (int i = 0; i < length(sortedList); i++) {
            char *lowerUsernmame = ToLower(username(sortedList.contents[i]));
            if (strcmp(lowerUsernmame, lowerData) == 0) {
                hasilCari.contents[length(hasilCari)] = sortedList.contents[i];
                length(hasilCari)++;
            }
        }
    } else if (basis == 3) {
        char* lowerData = ToLower(data);
        for (int i = 0; i < length(sortedList); i++) {
            char *lowerRiwayat = ToLower(riwayat(sortedList.contents[i]));
            if (strcmp(lowerRiwayat, lowerData) == 0) {
                hasilCari.contents[length(hasilCari)] = sortedList.contents[i];
                length(hasilCari)++;
            }
        }
    }

    printf("\n");
    if (pilihan == 1) {
        if (length(hasilCari) == 0) {
            printf("Tidak ditemukan pengguna dengan %s %s\n", basisCari, data);
        } else {
            printf("Menampilkan pengguna dengan %s %s...\n", basisCari, data);
            printf("\n");
            printf("-------------------------------------------------\n");
            printf("|-ID-|-----Nama-----|---Role---|----Penyakit----|\n");
            printf("-------------------------------------------------\n");
            

            for (int i = 0; i < length(hasilCari); i++) {
                if ((strcmp(role(hasilCari.contents[i]), "Dokter") == 0) || (strcmp(role(hasilCari.contents[i]), "Manager") == 0)) {
                    printf("| %.2d | %-12s | %-8s |       -        |\n", atoi(id(hasilCari.contents[i])), username(hasilCari.contents[i]), role(hasilCari.contents[i]));
                } else {
                    printf("| %.2d | %-12s | %-8s | %-14s |\n", atoi(id(hasilCari.contents[i])), username(hasilCari.contents[i]), role(hasilCari.contents[i]), riwayat(hasilCari.contents[i]));
                }
            }
            printf("-------------------------------------------------\n");
        }
	} else if (pilihan == 2) {
        if (length(hasilCari) == 0) {
            printf("Tidak ditemukan pengguna dengan %s %s\n", basisCari, data);
        } else {
            if (basis == 3) {
                int urutan, sort;
                char urutanLihat[5], sortLihat[11];
                MenuLihat(&urutan, &sort, urutanLihat, sortLihat);
                printf("Menampilkan pasien dengan %s %s dengan %s terurut %s...\n", basisCari, data, urutanLihat, sortLihat);
            }
            printf("--------------------------------------\n");
            printf("|-ID-|-----Nama-----|----Penyakit----|\n");
            printf("--------------------------------------\n");

            for (int i = 0; i < length(hasilCari); i++) {
                if (strcmp(role(hasilCari.contents[i]), "Pasien") == 0) {
                    printf("| %.2d | %-12s | %-14s |\n", atoi(id(hasilCari.contents[i])), username(hasilCari.contents[i]), riwayat(hasilCari.contents[i]));
                }
            }
            printf("--------------------------------------\n");
        }

	} else if (pilihan == 3) {
        if (length(hasilCari) == 0) {
            printf("Tidak ditemukan pengguna dengan %s %s\n", basisCari, data);
        } else {
            printf("---------------------\n");
            printf("|-ID-|-----Nama-----|\n");
            printf("---------------------\n");

            for (int i = 0; i < length(hasilCari); i++) {
                if (strcmp(role(hasilCari.contents[i]), "Dokter") == 0) {
                    printf("| %.2d | %-12s |\n", atoi(id(hasilCari.contents[i])), username(hasilCari.contents[i]));
                }
            }
            printf("---------------------\n");
        }
    }
}

void CariPasien (UserList uList) {
	UserList pasienList;
	length(pasienList) = 0;

	for (int i = 0; i < length(uList); i++) {
		if (strcmp(role(uList.contents[i]), "Pasien") == 0) {
			pasienList.contents[pasienList.len] = uList.contents[i];
			length(pasienList)++;
		}
	}

	CariUser(pasienList, 2);
}

void CariDokter (UserList uList) {
	UserList dokterList;
	length(dokterList) = 0;

	for (int i = 0; i < length(uList); i++) {
		if (strcmp(role(uList.contents[i]), "Dokter") == 0) {
			dokterList.contents[dokterList.len] = uList.contents[i];
			length(dokterList)++;
		}
	}

	CariUser(dokterList, 3);
}