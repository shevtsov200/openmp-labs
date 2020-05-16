#include <stdio.h>

#define N 2

void getCofactor(int mat[N][N], int n, int p, int q, int result[N][N]) 
{ 
    int i = 0, j = 0; 

    // Looping for each element of the matrix 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                result[i][j++] = mat[row][col]; 

                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
}

int calculateDeterminant(size_t n, int matrix[][n]){
    float ratio;
    int i, j, k;

    /* Conversion of matrix to upper triangular */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = matrix[j][i]/matrix[i][i];
				
                for(k = 0; k < n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    int determinant = 1; //storage for determinant
    for(i = 0; i < n; i++) {
        determinant *= matrix[i][i];
    }

    return determinant;
}

int main(int argc, char **argv) {
    int matrix[N][N] = {
        {1, 2},
        {3, 4}
    };

    int det = calculateDeterminant(N, matrix);

    printf("det is %d\n", det);

    return 0;
}
