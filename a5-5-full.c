#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
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
        p[i].remaining_time = p[i].burst_time;
        printf("Process %d Priority: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].completed = false;
    }
}

// FCFS Scheduling
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

// SJF Preemptive
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

// Priority Scheduling (Non-preemptive)
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
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", total_turnaround/n, total_waiting/n);
}

// Round Robin (Preemptive)
void round_robin(Process p[], int n, int quantum) {
    printf("\n--- Round Robin (Preemptive) ---\n");
    int time = 0, remain = n;
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

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", total_turnaround/n, total_waiting/n);
}

// Reset process data before each algorithm
void resetProcesses(Process original[], Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i] = original[i];
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }
}

int main() {
    Process original[MAX], p[MAX];
    int n, choice, quantum;

    inputProcesses(original, &n);

    do {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. FCFS\n2. SJF (Preemptive)\n3. Priority (Non-Preemptive)\n4. Round Robin\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);

        resetProcesses(original, p, n);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf_preemptive(p, n);
                break;
            case 3:
                priority_nonpreemptive(p, n);
                break;
            case 4:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                round_robin(p, n, quantum);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 0);

    return 0;
}
