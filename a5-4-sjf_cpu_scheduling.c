#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
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
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }
}

void sjf_preemptive(Process p[], int n) {
    printf("\n--- Shortest Job First (Preemptive) ---\n");
    int complete = 0, time = 0, min_index = -1;
    float total_waiting = 0, total_turnaround = 0;

    while (complete < n) {
        int min_burst = INT_MAX;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed && p[i].remaining_time < min_burst && p[i].remaining_time > 0) {
                min_burst = p[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        p[min_index].remaining_time--;
        time++;

        if (p[min_index].remaining_time == 0) {
            p[min_index].completed = true;
            complete++;
            p[min_index].completion_time = time;
            p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time;
            p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;
            total_waiting += p[min_index].waiting_time;
            total_turnaround += p[min_index].turnaround_time;
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", total_turnaround/n, total_waiting/n);
}

int main() {
    Process p[MAX];
    int n;

    inputProcesses(p, &n);
    sjf_preemptive(p, n);

    return 0;
}
