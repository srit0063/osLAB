#include <stdio.h>
#include <string.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    char type[10];
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct Process sq[n], uq[n];
    int sq_count = 0, uq_count = 0;

    for (int i = 0; i < n; i++) {
        int pid = i + 1;
        int at, bt;
        char ptype[10];

        printf("\n--- Process [%d] ---\n", pid);
        printf("Arrival Time: ");
        scanf("%d", &at);
        printf("Burst Time: ");
        scanf("%d", &bt);
        printf("Type (System/User): ");
        scanf("%s", ptype);

        if (strcmp(ptype, "System") == 0) {
            sq[sq_count].pid = pid;
            sq[sq_count].arrival_time = at;
            sq[sq_count].burst_time = bt;
            strcpy(sq[sq_count].type, ptype);
            sq_count++;
        } else {
            uq[uq_count].pid = pid;
            uq[uq_count].arrival_time = at;
            uq[uq_count].burst_time = bt;
            strcpy(uq[uq_count].type, ptype);
            uq_count++;
        }
    }

    for(int i=0; i<sq_count-1; i++) {
        for(int j=0; j<sq_count-i-1; j++) {
            if(sq[j].arrival_time > sq[j+1].arrival_time) {
                struct Process temp = sq[j];
                sq[j] = sq[j+1];
                sq[j+1] = temp;
            }
        }
    }

    for(int i=0; i<uq_count-1; i++) {
        for(int j=0; j<uq_count-i-1; j++) {
            if(uq[j].arrival_time > uq[j+1].arrival_time) {
                struct Process temp = uq[j];
                uq[j] = uq[j+1];
                uq[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    int sq_idx = 0, uq_idx = 0;

    printf("\n--- Execution Log ---\n");

    while (sq_idx < sq_count || uq_idx < uq_count) {
        if (sq_idx < sq_count) {
            if (current_time < sq[sq_idx].arrival_time) {
                current_time = sq[sq_idx].arrival_time;
            }

            printf("[%d - %d] System Process %d running\n", current_time, current_time + sq[sq_idx].burst_time, sq[sq_idx].pid);
            current_time += sq[sq_idx].burst_time;
            sq[sq_idx].completion_time = current_time;
            sq[sq_idx].turnaround_time = sq[sq_idx].completion_time - sq[sq_idx].arrival_time;
            sq[sq_idx].waiting_time = sq[sq_idx].turnaround_time - sq[sq_idx].burst_time;
            sq_idx++;
        }
        else if (uq_idx < uq_count) {
            if (current_time < uq[uq_idx].arrival_time) {
                current_time = uq[uq_idx].arrival_time;
            }

            printf("[%d - %d] User Process %d running\n", current_time, current_time + uq[uq_idx].burst_time, uq[uq_idx].pid);
            current_time += uq[uq_idx].burst_time;
            uq[uq_idx].completion_time = current_time;
            uq[uq_idx].turnaround_time = uq[uq_idx].completion_time - uq[uq_idx].arrival_time;
            uq[uq_idx].waiting_time = uq[uq_idx].turnaround_time - uq[uq_idx].burst_time;
            uq_idx++;
        }
    }

    float total_wt = 0, total_tat = 0;
    printf("\n%-5s %-8s %-5s %-5s %-5s %-5s %-5s\n", "PID", "Type", "Arr", "Brs", "Comp", "Wait", "TAT");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < sq_count; i++) {
        printf("%-5d %-8s %-5d %-5d %-5d %-5d %-5d\n",
               sq[i].pid, sq[i].type, sq[i].arrival_time, sq[i].burst_time,
               sq[i].completion_time, sq[i].waiting_time, sq[i].turnaround_time);
        total_wt += sq[i].waiting_time;
        total_tat += sq[i].turnaround_time;
    }
    for (int i = 0; i < uq_count; i++) {
        printf("%-5d %-8s %-5d %-5d %-5d %-5d %-5d\n",
               uq[i].pid, uq[i].type, uq[i].arrival_time, uq[i].burst_time,
               uq[i].completion_time, uq[i].waiting_time, uq[i].turnaround_time);
        total_wt += uq[i].waiting_time;
        total_tat += uq[i].turnaround_time;
    }

    printf("------------------------------------------------------------\n");
    printf("Average Waiting Time:    %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
