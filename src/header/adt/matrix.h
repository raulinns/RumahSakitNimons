#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_PASIEN 20

#define ROWS(M)         (M).rows
#define COLS(M)         (M).cols
#define MAXP(M)         (M).maxP
#define CNTN(M, i ,j)   (M).contents[i][j]

typedef struct {
    int rows;
    int cols;
    int contents[MAX_ROWS][MAX_COLS];
} Matrix;

void CreateMatrix(int rows, int cols, Matrix *M);

#endif