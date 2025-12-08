#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 1000

int readArrayFromFile(int arr[]) {
    FILE *file;
    int n;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open input file.\n");
        return -1;
    }

    fscanf(file, "%d", &n);
    if (n <= 1) {
        printf("Array must contain at least two elements.\n");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
    return n;
}

void findSecondSmallestLargest(int arr[], int n) {
    int smallest = INT_MAX, second_smallest = INT_MAX;
    int largest = INT_MIN, second_largest = INT_MIN;

    for (int i = 0; i < n; i++) {
        int num = arr[i];

        if (num < smallest) {
            second_smallest = smallest;
            smallest = num;
        } else if (num > smallest && num < second_smallest) {
            second_smallest = num;
        }

        
        if (num > largest) {
            second_largest = largest;
            largest = num;
        } else if (num < largest && num > second_largest) {
            second_largest = num;
        }
    }

    if (second_smallest == INT_MAX || second_largest == INT_MIN) {
        printf("Second smallest/largest element doesn't exist.\n");
    } else {
        printf("Second Smallest Element: %d\n", second_smallest);
        printf("Second Largest Element: %d\n", second_largest);
    }
}

int main() {
    int arr[MAX_SIZE];
    int n;

    n = readArrayFromFile(arr);
    if (n == -1) {
        return 1;
    }

    findSecondSmallestLargest(arr, n);

    return 0;
}






/*#include <stdio.h>

#define MAX_SIZE 1000

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int readArrayFromFile(int arr[]) {
    FILE *file;
    int n;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open input file.\n");
        return -1;
    }

    fscanf(file, "%d", &n);
    if (n <= 1) {
        printf("Array must contain at least two elements.\n");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
    return n;
}

void printSecondSmallestLargest(int arr[], int n) {
    int second_smallest = -1;
    int second_largest = -1;

    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[0]) {
            second_smallest = arr[i];
            break;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] != arr[n - 1]) {
            second_largest = arr[i];
            break;
        }
    }

    if (second_smallest == -1 || second_largest == -1) {
        printf("Second smallest/largest element does'not exist.\n");
    } else {
        printf("Second Smallest Element: %d\n", second_smallest);
        printf("Second Largest Element: %d\n", second_largest);
    }
}

int main() {
    int arr[MAX_SIZE];
    int n;

    n = readArrayFromFile(arr);
    if (n == -1) {
        return 1;
    }

    sortArray(arr, n);
    printSecondSmallestLargest(arr, n);

    return 0;
}
*/

