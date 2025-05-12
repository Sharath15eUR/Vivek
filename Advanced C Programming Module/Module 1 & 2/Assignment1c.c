#include <stdio.h>
#define N 4

int searchMatrix(int mat[N][N], int key) {
    int i, j;
    i = 0;
    j = N - 1; 

    while (i < N && j >= 0) {
        if (mat[i][j] == key)
            return 1;
        else if (mat[i][j] > key)
            j--;
        else
            i++;
    }
    return 0;
}

int main() {
    int mat[N][N] = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };

    int key;
    printf("Enter the value to check : ");
    scanf("%d", & key);

    if (searchMatrix(mat, key))
        printf("Key %d found in the matrix.\n", key);
    else
        printf("Key %d not found in the matrix.\n", key);

    return 0;
}

