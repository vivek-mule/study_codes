#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
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
        printf("Process %d Priority: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].completed = false;
    }
}

void priority_nonpreemptive(Process p[], int n) {
    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    int time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].waiting_time = time - p[idx].arrival_time;
            time += p[idx].burst_time;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].completed = true;
            completed++;

            total_waiting += p[idx].waiting_time;
            total_turnaround += p[idx].turnaround_time;
        } else {
            time++;
        }
    }

    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", total_turnaround/n, total_waiting/n);
}

int main() {
    Process p[MAX];
    int n;

    inputProcesses(p, &n);
    priority_nonpreemptive(p, n);

    return 0;
}
