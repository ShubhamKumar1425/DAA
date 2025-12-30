#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int n;
int cost[MAX+1][MAX+1];
int mst[MAX+1][MAX+1];

void prims(int start) {
    int parent[MAX+1], key[MAX+1], inMST[MAX+1];
    int i, u, v, totalCost = 0;

    /* Initialize */
    for (i = 1; i <= n; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
        parent[i] = -1;
    }
    key[start] = 0;

    /* Build MST (select each vertex once) */
    for (int count = 1; count <= n; count++) {
        u = -1;
        /* Pick vertex u not in MST with minimum key.
           If keys tie, prefer the vertex with larger index (to match expected output). */
        for (i = 1; i <= n; i++) {
            if (!inMST[i]) {
                if (u == -1 ||
                    key[i] < key[u] ||
                    (key[i] == key[u] && i > u)) {
                    u = i;
                }
            }
        }

        if (u == -1) break; /* Shouldn't happen for connected graph */

        inMST[u] = 1;

        /* Update keys of adjacent vertices */
        for (v = 1; v <= n; v++) {
            if (cost[u][v] != 0 && !inMST[v] && cost[u][v] < key[v]) {
                key[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }

    /* Initialize MST matrix to zeros */
    for (i = 1; i <= n; i++)
        for (v = 1; v <= n; v++)
            mst[i][v] = 0;

    /* Build adjacency matrix from parent[] */
    for (i = 1; i <= n; i++) {
        if (parent[i] != -1) {
            u = parent[i];
            v = i;
            mst[u][v] = mst[v][u] = cost[u][v];
            totalCost += cost[u][v];
        }
    }

    /* Print MST adjacency matrix */
    printf("\nCost Adjacency Matrix of MST:\n");
    for (i = 1; i <= n; i++) {
        for (v = 1; v <= n; v++) {
            printf("%d\t", mst[i][v]);
        }
        printf("\n");
    }

    printf("\nTotal Weight of the Spanning Tree: %d\n", totalCost);
}

int main() {
    FILE *fp;
    int i, j, start;

    fp = fopen("inUnAdjMat.dat", "r");
    if (!fp) {
        printf("Error opening file 'inUnAdjMat.dat'\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter the Starting Vertex (1 to %d): ", n);
    if (scanf("%d", &start) != 1) return 1;

    /* Read adjacency matrix (1..n, 1..n) from file */
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (fscanf(fp, "%d", &cost[i][j]) != 1) {
                printf("Error reading adjacency matrix from file.\n");
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);

    prims(start);

    return 0;
}
