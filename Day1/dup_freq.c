#include <stdio.h>

int arr[100], freq[100], n;

void readArrayFromFile() {
    FILE *fp = fopen("input2.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        n = 0;
        return;
    }

    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);
}

void countFrequencies() {
    for (int i = 0; i < n; i++) {
        freq[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int count = 1;
        if (freq[i] != 0) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                    freq[j] = 0;
                }
            }
            freq[i] = count;
        }
    }
}

int countDuplicateElements() {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (freq[i] > 1) {
            total++;
        }
    }
    return total;
}

int findMostRepeating() {
    int max = 0, element = -1;
    for (int i = 0; i < n; i++) {
        if (freq[i] > max) {
            max = freq[i];
            element = arr[i];
        }
    }
    return element;
}

int findMaxFrequency() {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (freq[i] > max) {
            max = freq[i];
        }
    }
    return max;
}

int main() {
    readArrayFromFile();
    if (n == 0) return 1;

    countFrequencies();

    int totalDuplicates = countDuplicateElements();
    int mostRepeating = findMostRepeating();
    int maxFreq = findMaxFrequency();

    printf("Total number of duplicate elements = %d\n", totalDuplicates);
    printf("Most repeating element = %d ,repeated %d times. \n", mostRepeating, maxFreq);

    return 0;
}
