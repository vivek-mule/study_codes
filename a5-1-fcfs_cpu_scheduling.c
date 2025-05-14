#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
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
    }
}

void fcfs(Process p[], int n) {
    printf("\n--- First Come First Serve (FCFS) ---\n");
    int time = 0;
    float total_waiting = 0, total_turnaround = 0;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].arrival_time > p[j + 1].arrival_time)
                { Process temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp; }

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;

        p[i].waiting_time = time - p[i].arrival_time;
        time += p[i].burst_time;
        p[i].completion_time = time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

        total_waiting += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
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
    fcfs(p, n);

    return 0;
}
