#include <stdio.h>

#define MAX 20

// Calculate Need Matrix = Max - Allocation
void calculateNeed(int need[MAX][MAX], int max[MAX][MAX],
                   int allocation[MAX][MAX], int n, int m) {
    int i, j;

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Print Matrix
void printMatrix(int matrix[MAX][MAX], char title[],
                 int n, int m) {
    int i, j;

    printf("\n%s:\n", title);

    printf("      ");
    for(j = 0; j < m; j++) {
        printf("R%d   ", j);
    }
    printf("\n");

    for(i = 0; i < n; i++) {
        printf("P%d   ", i);

        for(j = 0; j < m; j++) {
            printf("%-5d", matrix[i][j]);
        }
        printf("\n");
    }
}

// Banker's Safety Algorithm
int isSafe(int processes[], int available[],
           int max[MAX][MAX],
           int allocation[MAX][MAX],
           int n, int m) {

    int need[MAX][MAX];
    calculateNeed(need, max, allocation, n, m);

    int work[MAX];
    int finish[MAX] = {0};
    int safeSeq[MAX];

    int i, j;

    for(i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is in UNSAFE state.\n");
            printf("Deadlock may occur.\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state.\n");
    printf("Safe Sequence: ");

    for(i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);

        if(i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 1;
}

int main() {

    int n, m;
    int allocation[MAX][MAX];
    int max[MAX][MAX];
    int need[MAX][MAX];
    int available[MAX];
    int processes[MAX];

    int i, j;

    printf("===== Banker's Algorithm =====\n\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    for(i = 0; i < n; i++)
        processes[i] = i;

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for(i = 0; i < n; i++) {
        printf("Process P%d: ", i);

        for(j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");

    for(i = 0; i < n; i++) {
        printf("Process P%d: ", i);

        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");

    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix
    calculateNeed(need, max, allocation, n, m);

    // Display Matrices
    printMatrix(allocation, "Allocation Matrix", n, m);
    printMatrix(max, "Max Matrix", n, m);
    printMatrix(need, "Need Matrix", n, m);

    printf("\nAvailable Resources: ");

    for(i = 0; i < m; i++) {
        printf("%d ", available[i]);
    }

    printf("\n\n========================================\n");

    // Check Safe State
    isSafe(processes, available, max, allocation, n, m);

    printf("========================================\n");

    return 0;
}