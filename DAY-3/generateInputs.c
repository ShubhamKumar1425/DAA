#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateAscending(const char *filename, int start, int n) {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", start + i);
    fclose(fp);
}
void generateDescending(const char *filename, int start, int n) {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", start - i);
    fclose(fp);
}
void generateRandom(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    srand(time(0));
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", rand() % 1000);
    fclose(fp);
}

int main() {
    int size = 400;  // You can set between 300–500

    generateAscending("inAsce.dat", 1, size);
    generateDescending("inDesc.dat", size, size);
    generateRandom("inRand.dat", size);

    printf("Input files generated successfully.\n");
    return 0;
}

