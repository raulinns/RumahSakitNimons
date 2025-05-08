#include "../header/denah.h"
#include "../header/user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CreateDenah(Matrix *denah) {
    FILE *configFile = fopen("../file/config.txt", "r");
    char line[MAX_LINE_LENGTH];
    int i = 0, j, k = 0;
    fgets(line, MAX_LINE_LENGTH, configFile);
    int rows = 0, cols = 0, maxP = 0;
    rows = atoi(ParseData(line, i, ' '));
    cols = atoi(ParseData(line, i, '\n'));
    i = 0;
    fgets(line, MAX_LINE_LENGTH, configFile);
    maxP = atoi(ParseData(line, i, '\n'));
    CreateMatrix(rows, cols, maxP, denah);
    for (i = 0; i < ROWS(*denah); i++) {
        for (j = 0; j < COLS(*denah); j++) {
            fgets(line, MAX_LINE_LENGTH, configFile);
            int cnt = 0;
            for (k = 0; k < MAXP(*denah) + 1 || line[cnt] != '\n' || line[cnt] != '\0'; k++) {
                ELMT(*denah, i, j, k) = atoi(ParseData(line, cnt, ' '));
            }
        }
    }
}

void PrintDenah(Matrix denah) {
    int i, j;
    printf(" ");
    for (i = 0; i < denah.cols; i++) {
        printf("     %d", i + 1);
    }
    printf("\n   +");
    for (i = 0; i <denah.cols; i++) {
        printf("-----+");
    }
    printf("\n");
    for (i = 0; i < denah.rows; i++) {
        printf(" %c  |", (char)(i + 65));
        for (j = 0; j < denah.cols; j++) {
            printf(" %c%d  |", (char)(i + 65), j + 1);
        }
        printf("   +");
        for (j = 0; j < denah.cols; j++) {
            printf("-----+");
        }
        printf("\n");
    }
}

void PrintRuang(char *ruang, Matrix denah) {
    printf("--- Detail Ruangan %s ---\n", ruang);
    printf("Kapasitas  : %d\n", denah.maxP);
    int i = 0;
    ParseData(ruang, i, ' ');
    i++;
    int row = (int)ruang[i] - (int)('A');
    i++;
    int col = 0;
    col = atoi(ParseData(ruang, i, ' ')) - 1;
    printf("Dokter     : ");
    if (denah.contents[row][col][0] != 0) {
        printf("Dr. %s", NamaUser(denah.contents[row][col][0]));
    }
    else {
        printf("-");
    }
    printf("\n");
    printf("Pasien di dalam ruangan:\n");
    if (denah.contents[row][col][1] != 0) {
        for (i = 1; denah.contents[row][col][i] != 0; i++) {
            printf("  %d. %s\n", i, NamaUser(denah.contents[row][col][i]));
        }
    }
    else {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    printf("------------------------------\n");
}

void UbahDenah(char *luas, Matrix *denah) {
    int i = 0;
    ParseData(luas, i, ' ');
    int rows = ParseData(luas, i, ' ');
    int cols = ParseData(luas, i, ' ');
    int valid = 1;
    if (denah->rows > rows && denah->cols > cols) {
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (i >= rows && j >= cols) {
                    if (ELMT(*denah, i, j, 0) != 0) {
                        printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(ELMT(*denah, i, j, 0)));
                        valid = 0;
                        break;
                    }
                }
            }
        }
    }
    else if (denah->rows > rows) {
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (i >= rows) {
                    if (ELMT(*denah, i, j, 0) != 0) {
                        printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(ELMT(*denah, i, j, 0)));
                        valid = 0;
                        break;
                    }
                }
            }
        }
    }
    else if (denah->cols > cols) {
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (j >= cols) {
                    if (ELMT(*denah, i, j, 0) != 0) {
                        printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", (i + (int)('A')), j, NamaUser(ELMT(*denah, i, j, 0)));
                        valid = 0;
                        break;
                    }
                }
            }
        }
    }
    if (valid) {
        denah->rows = rows;
        denah->cols = cols;
        printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom\n", rows, cols);
    }
}