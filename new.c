#include <stdio.h>
#include <stdlib.h>

// Function to compare two rows for qsort
int compareRows(const void *a, const void *b) {
    const int *rowA = *(const int **)a;
    const int *rowB = *(const int **)b;

    // Compare the first element of each row
    return rowA[0] - rowB[0];
}

int main() {
    int rows = 3;
    int cols = 2;

    int arr[3][2] = {{2, 3}, {1, 5}, {4, 0}};

    // Sort the 2D array by the first column
    qsort(arr, rows, sizeof(arr[0]), compareRows);

    // Print the sorted array
    printf("Sorted 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
