#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
};

int main() {
    int n, i, j;

    printf("===== First Come First Serve (FCFS) Scheduling =====\n\n");

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for(i = 0; i < n; i++) {
        printf("\nProcess P%d:\n", i + 1);

        printf("  Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("  Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].pid = i + 1;
    }

    // Sort processes by arrival time (FCFS rule)
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int current_time = 0;
    int total_waiting = 0;
    int total_turnaround = 0;

    printf("\n-------------------------------------------------------------------------------\n");
    printf("Process   Arrival   Burst   Start   Completion   Waiting   Turnaround\n");
    printf("-------------------------------------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        int start_time;

        if(current_time < p[i].arrival)
            start_time = p[i].arrival;
        else
            start_time = current_time;

        int completion_time = start_time + p[i].burst;
        int turnaround_time = completion_time - p[i].arrival;
        int waiting_time = turnaround_time - p[i].burst;

        total_waiting += waiting_time;
        total_turnaround += turnaround_time;

        printf("P%-8d %-9d %-7d %-7d %-12d %-9d %-10d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               start_time,
               completion_time,
               waiting_time,
               turnaround_time);

        current_time = completion_time;
    }

    float avg_waiting = (float)total_waiting / n;
    float avg_turnaround = (float)total_turnaround / n;

    printf("-------------------------------------------------------------------------------\n");
    printf("\nAverage Waiting Time    : %.2f\n", avg_waiting);
    printf("Average Turnaround Time : %.2f\n", avg_turnaround);
    printf("-------------------------------------------------------------------------------\n");

    return 0;
}