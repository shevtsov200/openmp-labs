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



int main(int argc, char **argv) {
    return 0;
}
