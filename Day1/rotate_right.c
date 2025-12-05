#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int arr[], int p2) {
    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(&arr[i], &arr[i - 1]);
    }
}

int main() {
    int A[100], N;

    printf("Enter the size of array N: ");
    scanf("%d", &N);

    printf("Enter an array A of size %d: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    printf("Before ROTATE: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    ROTATE_RIGHT(A, 5);

    printf("After ROTATE: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
