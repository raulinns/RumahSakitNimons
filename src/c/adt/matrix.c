#include "../header/adt/matrix.h"

void CreateMatrix(int rows, int cols, int maxP, Matrix *M) {
    ROWS(*M) = rows; COLS(*M) = cols; MAXP(*M) = maxP;   
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < maxP; k++) {
                ELMT(*M, i, j, k) = 0;
            }
        }
    }
}