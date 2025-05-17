#include <stdio.h>

void rearrangeEvenOdd(int *arr, int size) {
    int temp[100];
    int i;
    int *evenPtr = temp;
    int *oddPtr = temp + size - 1;
    int *ptr;

    for (i = 0; i < size; i++) {
        if (*(arr + i) % 2 == 0)
            *evenPtr++ = *(arr + i);
        else
            *oddPtr-- = *(arr + i);
    }

    ptr = temp;
    while (ptr < evenPtr) {
        *arr++ = *ptr++;
    }

    ptr = temp + size - 1;
    while (ptr > oddPtr) {
        *arr++ = *ptr--;
    }
}

void printArray(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", *(arr + i));
    printf("\n");
}

int main() {
    int arr[] = {3, 2, 4, 1, 5, 6};
    int size = sizeof(arr)/sizeof(arr[0]);

    rearrangeEvenOdd(arr, size);
    printArray(arr, size);

    return 0;
}

