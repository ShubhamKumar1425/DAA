#include <stdio.h>
#include <stdlib.h>
#define BITS 16

void toBinary(int num, char binary[], int index) {
    if (index < 0) return;
    binary[index] = (num % 2) + '0';
    toBinary(num / 2, binary, index - 1);
}
void DecToBin(int n, char inputFile[], char outputFile[]) {
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");
    int i, num;
    char binary[BITS + 1];

    if (fin == NULL || fout == NULL) {
        printf("Error: Cannot open file.\n");
        exit(1);
    }
    for (i = 0; i < n && fscanf(fin, "%d", &num) == 1; i++) {
        for (int j = 0; j < BITS; j++) binary[j] = '0';
        binary[BITS] = '\0';

        toBinary(num, binary, BITS - 1);
        fprintf(fout, "The binary equivalent of %d is %s\n", num, binary);
    }

    fclose(fin);
    fclose(fout);
}

void displayOutput(char outputFile[]) {
    FILE *fout = fopen(outputFile, "r");
    char line[100];

    if (fout == NULL) {
        printf("Error: Cannot open output file for reading.\n");
        exit(1);
    }

    printf("Output:\n");
    while (fgets(line, sizeof(line), fout) != NULL) {
        printf("%s", line);
    }

    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    DecToBin(n, argv[2], argv[3]);
    displayOutput(argv[3]);

    return 0;
}





