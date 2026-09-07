#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, tq, i, j;

    printf("===== Round Robin (RR) CPU Scheduling =====\n\n");

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    struct Process p[n];

    // Input process details
    for(i = 0; i < n; i++) {
        printf("\nProcess P%d:\n", i + 1);

        printf("  Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("  Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    // Sort by arrival time
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int queue[100];
    int front = 0, rear = 0;

    int current_time = 0;
    int completed = 0;
    int arrived = 0;
    int visited[n];

    for(i = 0; i < n; i++)
        visited[i] = 0;

    // Add processes that arrive at time 0
    while(arrived < n && p[arrived].arrival <= current_time) {
        queue[rear++] = arrived;
        visited[arrived] = 1;
        arrived++;
    }

    while(completed < n) {

        if(front == rear) {
            current_time = p[arrived].arrival;

            while(arrived < n &&
                  p[arrived].arrival <= current_time) {
                queue[rear++] = arrived;
                visited[arrived] = 1;
                arrived++;
            }
            continue;
        }

        int idx = queue[front++];

        int exec_time =
            (p[idx].remaining < tq) ?
            p[idx].remaining : tq;

        p[idx].remaining -= exec_time;
        current_time += exec_time;

        // Add newly arrived processes
        while(arrived < n &&
              p[arrived].arrival <= current_time) {
            queue[rear++] = arrived;
            visited[arrived] = 1;
            arrived++;
        }

        if(p[idx].remaining > 0) {
            queue[rear++] = idx;
        }
        else {
            p[idx].completion = current_time;
            p[idx].turnaround =
                p[idx].completion - p[idx].arrival;
            p[idx].waiting =
                p[idx].turnaround - p[idx].burst;
            completed++;
        }
    }

    float total_waiting = 0;
    float total_turnaround = 0;

    printf("\n-------------------------------------------------------------------------------------\n");
    printf("Process   Arrival   Burst   Completion   Waiting   Turnaround\n");
    printf("-------------------------------------------------------------------------------------\n");

    // Sort by Process ID for display
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].pid > p[j].pid) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for(i = 0; i < n; i++) {
        printf("P%-8d %-9d %-7d %-12d %-9d %-10d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].waiting,
               p[i].turnaround);

        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("-------------------------------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    : %.2f\n",
           total_waiting / n);

    printf("Average Turnaround Time : %.2f\n",
           total_turnaround / n);

    printf("-------------------------------------------------------------------------------------\n");

    return 0;
}