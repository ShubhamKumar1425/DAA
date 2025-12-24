#include <stdio.h>

// i) maxmin1: print max and min inside the function
void maxmin1(int a[], int s, int e) {
    int max = a[s], min = a[s];
    for (int i = s + 1; i <= e; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    printf("maxmin1 -> Max: %d, Min: %d\n", max, min);
}

// ii) maxmin2: return pointer to array where max and min are stored
int* maxmin2(int a[], int s, int e) {
    static int res[2];
    res[0] = a[s]; // max
    res[1] = a[s]; // min
    for (int i = s + 1; i <= e; i++) {
        if (a[i] > res[0]) res[0] = a[i];
        if (a[i] < res[1]) res[1] = a[i];
    }
    return res;
}

// iii) maxmin3: store max and min in pointer variables passed by caller
void maxmin3(int a[], int s, int e, int *min, int *max) {
    *max = a[s];
    *min = a[s];
    for (int i = s + 1; i <= e; i++) {
        if (a[i] > *max) *max = a[i];
        if (a[i] < *min) *min = a[i];
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // i) maxmin1
    maxmin1(arr, 0, n - 1);

    // ii) maxmin2
    int *result = maxmin2(arr, 0, n - 1);
    printf("maxmin2 -> Max: %d, Min: %d\n", result[0], result[1]);

    // iii) maxmin3
    int minVal, maxVal;
    maxmin3(arr, 0, n - 1, &minVal, &maxVal);
    printf("maxmin3 -> Max: %d, Min: %d\n", maxVal, minVal);

    return 0;
}
