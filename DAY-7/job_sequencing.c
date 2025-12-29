#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];     
    int deadline; 
    int profit;   
} Job;

int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;
}

int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++)
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    return max;
}

void jobScheduling(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline + 1];    
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = -1;

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i; 
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Scheduled jobs: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%s ", jobs[slot[i]].id);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    printf("Enter Job ID, Deadline and Profit:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobScheduling(jobs, n);
    return 0;
}
