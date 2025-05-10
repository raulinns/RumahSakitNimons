#include "../header/adt/matrix.h"

void CreateMatrix(int rows, int cols, Matrix *M) {
    ROWS(*M) = rows; COLS(*M) = cols;  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            CNTN(*M, i, j) = 0;
        }
    }
}