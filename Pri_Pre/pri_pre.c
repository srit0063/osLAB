#include <stdio.h>

struct Process {
    int pid, at, bt, rt, priority, ct, wt, tat;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i=0; i<n; i++) {
        p[i].pid = i+1;
        printf("Enter AT, BT and Priority for P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0, min_pri;
    int shortest = -1, check = 0;


    int gc[1000], gc_time[1000], gc_index = 0;

    while(completed != n) {
        min_pri = 10000;
        shortest = -1;
        check = 0;

        for(int i=0; i<n; i++) {
            if((p[i].at <= time) && (p[i].rt > 0) && (p[i].priority < min_pri)) {
                min_pri = p[i].priority;
                shortest = i;
                check = 1;
            }
        }

        if(check == 0) {
            time++;
            continue;
        }

        p[shortest].rt--;
        time++;

        if(p[shortest].rt == 0) {
            completed++;
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
    }

    printf("\nPID\tAT\tBT\tPri\tCT\tWT\tTAT\n");
    int sum_ct=0, sum_wt=0, sum_tat=0;
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].wt, p[i].tat);
        sum_ct += p[i].ct;
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }

    printf("\nAverage CT: %.2f", (float)sum_ct/n);
    printf("\nAverage WT: %.2f", (float)sum_wt/n);
    printf("\nAverage TAT: %.2f\n", (float)sum_tat/n);

    for(int i=0; i<gc_index; i++) {
        printf("%d    ", gc_time[i]);
    }
    printf("%d\n", time);

    return 0;
}
