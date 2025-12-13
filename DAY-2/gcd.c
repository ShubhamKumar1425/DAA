#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    FILE *inFile, *outFile;
    int x, y, result;

    if (argc != 3) {
        printf("Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    inFile = fopen(argv[1], "r");
    outFile = fopen(argv[2], "w");

    if (inFile == NULL || outFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int count = 0;

    while (fscanf(inFile, "%d %d", &x, &y) == 2) {
        result = gcd(x, y);
        fprintf(outFile, "The GCD of %d and %d is %d\n", x, y, result);
        count++;
    }

    fclose(inFile);
    fclose(outFile);

    if (count < 20) {
        printf("Less than 20 pairs were found in the input file.\n");
    }

    outFile = fopen(argv[2], "r");
    if (outFile == NULL) {
        printf("Cannot open output file to display.\n");
        return 1;
    }

    printf("Output:\n");
    char line[100];
    while (fgets(line, sizeof(line), outFile)) {
        printf("%s", line);
    }

    fclose(outFile);

    return 0;
}
