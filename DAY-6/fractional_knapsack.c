#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int   item_id;
    double profit;
    double weight;
    double ratio;            
    double fraction_taken;   
} ITEM;

static void swap(ITEM *a, ITEM *b) {
    ITEM t = *a; *a = *b; *b = t;
}

static void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if (l < n && arr[l].ratio > arr[largest].ratio) largest = l;
    if (r < n && arr[r].ratio > arr[largest].ratio) largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

static void heapSortAscending(ITEM arr[], int n) {
    for (int i = n/2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

static void reverse(ITEM arr[], int n) {
    for (int i = 0; i < n/2; ++i) swap(&arr[i], &arr[n-1-i]);
}

int main(void) {
    int n;
    double capacity;

    printf("Enter the number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    ITEM *items = (ITEM*)malloc(n * sizeof(ITEM));
    if (!items) return 0;

    for (int i = 0; i < n; ++i) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%lf %lf", &items[i].profit, &items[i].weight);
        items[i].item_id = i + 1;
        items[i].ratio   = items[i].profit / items[i].weight;
        items[i].fraction_taken = 0.0;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%lf", &capacity);

    heapSortAscending(items, n);
    reverse(items, n);

    double remaining = capacity;
    double max_profit = 0.0;

    for (int i = 0; i < n; ++i) {
        if (remaining <= 0.0) break;

        if (items[i].weight <= remaining) {
            items[i].fraction_taken = 1.0;
            max_profit += items[i].profit;
            remaining  -= items[i].weight;
        } else {
            items[i].fraction_taken = remaining / items[i].weight;
            max_profit += items[i].profit * items[i].fraction_taken;
            remaining = 0.0;
            break;
        }
    }

    printf("\nItem No   \tprofit  \tWeight    \t\tAmount to be taken\n");
    for (int i = 0; i < n; ++i) {
        printf("%-8d\t%f\t%f\t\t%f\n",
               items[i].item_id, items[i].profit, items[i].weight, items[i].fraction_taken);
    }
    printf("\nMaximum profit: %f\n", max_profit);

    free(items);
    return 0;
}
