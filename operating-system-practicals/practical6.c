#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completed;
};

int main() {
    int n, i;

    printf("===== Priority Scheduling (Non-Preemptive) =====\n");
    printf("Note: Lower priority number means Higher priority\n\n");

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

        printf("  Priority: ");
        scanf("%d", &p[i].priority);

        p[i].pid = i + 1;
        p[i].completed = 0;
    }

    int current_time = 0;
    int completed = 0;
    int total_waiting = 0;
    int total_turnaround = 0;

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("Process   Arrival   Burst   Priority   Start   Completion   Waiting   Turnaround\n");
    printf("------------------------------------------------------------------------------------------\n");

    while(completed < n) {
        int selected = -1;
        int highest_priority = 99999;

        // Find highest priority process among arrived processes
        for(i = 0; i < n; i++) {
            if(p[i].arrival <= current_time &&
               p[i].completed == 0) {

                if(p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    selected = i;
                }
                else if(p[i].priority == highest_priority) {
                    if(p[i].arrival < p[selected].arrival)
                        selected = i;
                }
            }
        }

        // No process available
        if(selected == -1) {
            int next_arrival = 99999;

            for(i = 0; i < n; i++) {
                if(p[i].completed == 0 &&
                   p[i].arrival < next_arrival) {
                    next_arrival = p[i].arrival;
                }
            }

            current_time = next_arrival;
            continue;
        }

        int start_time = current_time;
        int completion_time = start_time + p[selected].burst;
        int turnaround_time = completion_time - p[selected].arrival;
        int waiting_time = turnaround_time - p[selected].burst;

        total_waiting += waiting_time;
        total_turnaround += turnaround_time;

        printf("P%-8d %-9d %-7d %-10d %-7d %-12d %-9d %-10d\n",
               p[selected].pid,
               p[selected].arrival,
               p[selected].burst,
               p[selected].priority,
               start_time,
               completion_time,
               waiting_time,
               turnaround_time);

        p[selected].completed = 1;
        current_time = completion_time;
        completed++;
    }

    float avg_waiting = (float)total_waiting / n;
    float avg_turnaround = (float)total_turnaround / n;

    printf("------------------------------------------------------------------------------------------\n");
    printf("\nAverage Waiting Time    : %.2f\n", avg_waiting);
    printf("Average Turnaround Time : %.2f\n", avg_turnaround);
    printf("------------------------------------------------------------------------------------------\n");

    return 0;
}