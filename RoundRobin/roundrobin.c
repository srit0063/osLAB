#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    struct Process p[n];
    int rem_bt[n];
    int readyQ[100];
    int front = 0, rear = 0;

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
        p[i].pid = i + 1;
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        rem_bt[i] = p[i].bt;
        p[i].rt = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    int time = 0, completed = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            readyQ[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].at <= time) {
                    readyQ[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = readyQ[front++];

        if (rem_bt[idx] > tq) {
            time += tq;
            rem_bt[idx] -= tq;
            p[idx].rt = rem_bt[idx];
        } else {
            time += rem_bt[idx];
            rem_bt[idx] = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = 0;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= time) {
                readyQ[rear++] = i;
                visited[i] = 1;
            }
        }

        if (rem_bt[idx] > 0) {
            readyQ[rear++] = idx;
        }
    }

    printf("\nRound Robin Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt);
    }

    float avg_TAT = 0, avg_WT = 0;
    for (int i = 0; i < n; i++) {
        avg_TAT += p[i].tat;
        avg_WT += p[i].wt;
    }

    printf("\nAverage turnaround time: %.2f ms\n", avg_TAT / n);
    printf("Average waiting time: %.2f ms\n", avg_WT / n);


    return 0;
}
