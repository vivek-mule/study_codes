#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void inputProcesses(Process p[], int *n) {
    printf("Enter number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }
}

void round_robin(Process p[], int n, int quantum) {
    printf("\n--- Round Robin (Preemptive) ---\n");
    int time = 0;
    float total_waiting = 0, total_turnaround = 0;
    bool done;

    while (true) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                done = false;
                if (p[i].remaining_time > quantum) {
                    time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].burst_time - p[i].arrival_time;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].completion_time = time;
                    total_waiting += p[i].waiting_time;
                    total_turnaround += p[i].turnaround_time;
                    p[i].remaining_time = 0;
                }
            }
        }
        if (done)
            break;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", total_turnaround / n, total_waiting / n);
}

int main() {
    Process p[MAX];
    int n, quantum;

    inputProcesses(p, &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    round_robin(p, n, quantum);

    return 0;
}
