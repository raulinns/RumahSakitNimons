#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_PASIEN 20

#define ROWS(M) (M).rows
#define COLS(M) (M).cols
#define MAXP(M) (M).maxP
#define ELMT(M, i ,j, k) (M).contents[i][j][k]

typedef struct {
    int rows;
    int cols;
    int maxP;
    int contents[MAX_ROWS][MAX_COLS][MAX_PASIEN];
} Matrix;

void CreateMatrix(int rows, int cols, int maxPasien, Matrix *M);

#endif