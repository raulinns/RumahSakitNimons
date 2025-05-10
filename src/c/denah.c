#include "../header/denah.h"
#include "../header/user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CreateDenah(Denah *denah) {
    FILE *configFile = fopen("../file/config.txt", "r");
    char line[MAX_LINE_LENGTH];
    int i = 0, j, k = 0;
    fgets(line, MAX_LINE_LENGTH, configFile);
    int rows = atoi(ParseData(line, i, ' '));
    int cols = atoi(ParseData(line, i, ' '));
    ROWS(MAT(*denah)) = rows;
    COLS(MAT(*denah)) = cols;
    fgets(line, MAX_LINE_LENGTH, configFile);
    int nEff = atoi(ParseData(line, i, ' '));
    NEFF(LIST(*denah)) = nEff + nEff * cols + nEff * cols * rows;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            CNTN(MAT(*denah), i, j);
            int l = 0;
            for (k = 0; k < nEff && line[l] != '\0' && line[l] != '\n' && line[l] != '0'; k++) {
                ELMT(LIST(*denah), i * cols * nEff + j * nEff + k) = ParseData(line, l, ' ');
            }
        }
    }
}

void PrintDenah(Denah denah) {
    int i, j;
    printf(" ");
    for (i = 0; i < COLS(MAT(denah)); i++) {
        printf("     %d", i + 1);
    }
    printf("\n   +");
    for (i = 0; i < COLS(MAT(denah)); i++) {
        printf("-----+");
    }
    printf("\n");
    for (i = 0; i < ROWS(MAT(denah)); i++) {
        printf(" %c  |", (char)(i + 65));
        for (j = 0; j < COLS(MAT(denah)); j++) {
            printf(" %c%d  |", (char)(i + 65), j + 1);
        }
        printf("   +");
        for (j = 0; j < COLS(MAT(denah)); j++) {
            printf("-----+");
        }
        printf("\n");
    }
}

void PrintRuang(char *ruang, Denah denah) {
    int i = 15;
    int row = (int)ruang[i] - (int)('A');
    i++;
    int col = atoi(ParseData(ruang, i, ' ')) - 1;
    if (row < ROWS(MAT(denah)) && row >= 0 && col < COLS(MAT(denah)) && col >= 0) {
        printf("--- Detail Ruangan %s ---\n", ruang);
        printf("Kapasitas  : %d\n", NEFF(LIST(denah)));
        printf("Dokter     : ");
        if (CNTN(MAT(denah), row, col) != 0) {
            printf("Dr. %s", NamaUser(CNTN(MAT(denah), row, col)));
        }
        else {
            printf("-");
        }
        printf("\n");
        printf("Pasien di dalam ruangan:\n");
        if (ELMT(LIST(denah), row * COLS(MAT(denah)) * NEFF(LIST(denah)) + col * NEFF(LIST(denah))) != 0) {
            for (i = 0; ELMT(LIST(denah), row * COLS(MAT(denah)) * NEFF(LIST(denah)) + col * NEFF(LIST(denah)) + i) != 0; i++) {
                printf("  %d. %s\n", i + 1, NamaUser(ELMT(LIST(denah), row * COLS(MAT(denah)) * NEFF(LIST(denah)) + col * NEFF(LIST(denah)) + i)));
            }
        }
        else {
            printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
        }
        printf("------------------------------\n");
    }
}

void UbahDenah(char *luas, Denah *denah) {
    int i = 0;
    ParseData(luas, i, ' ');
    int rows = atoi(ParseData(luas, i, ' '));
    int cols = atoi(ParseData(luas, i, ' '));
    int valid = 1;
    if (ROWS(MAT(*denah)) > rows && COLS(MAT(*denah)) > cols) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (i >= rows && j >= cols && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    else if (ROWS(MAT(*denah)) > rows) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (i >= rows && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    else if (COLS(MAT(*denah)) > cols) {
        for (int i = 0; i < ROWS(MAT(*denah)); i++) {
            for (int j = 0; j < COLS(MAT(*denah)); j++) {
                if (j >= cols && CNTN(MAT(*denah), i, j) != 0) {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(CNTN(MAT(*denah), i, j)));
                    valid = 0;
                    break;
                }
            }
        }
    }
    if (valid) {
        ROWS(MAT(*denah)) = rows;
        COLS(MAT(*denah)) = cols;
        printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom\n", rows, cols);
    }
}