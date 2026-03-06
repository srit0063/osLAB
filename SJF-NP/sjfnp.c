#include <stdio.h>
//SJF Non-Premptive Code
//Input - List of processes (PID, AT, BT)
//Output - CT, TAT, WT



 struct Process{
        int pid;
        int at;
        int bt;
        int ct;
        int tat;
        int wt;
        int is_completed;
    };

void main(){
    int n,i,j, completed=0;
    struct Process proc[10], temp;
    int curTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    float avgTime=0.0, waitTime=0.0;
    for (i=0;i<n;i++){
        printf("Enter Arrival and Burst Times for P%d: ", i+1);
        proc[i].pid = i+1;
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].is_completed = 0;
    }

    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
                if(proc[j].at>proc[j+1].at){
                    temp = proc[j];
                    proc[j]=proc[j+1];
                    proc[j+1]=temp;
        }
    }
}

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    while (completed< n) {
        int idx = -1;
        int min_bt = 100;
        for (i = 0; i < n; i++) {
            if (proc[i].at <= curTime && proc[i].is_completed == 0) {
                if (proc[i].bt < min_bt) {
                    min_bt = proc[i].bt;
                    idx = i;
                }
                if (proc[i].bt == min_bt) {
                    if (proc[i].at < proc[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            proc[idx].ct = curTime + proc[idx].bt;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            proc[idx].is_completed = 1;

            curTime = proc[idx].ct;
            completed++;

            avgTime += proc[idx].tat;
            waitTime += proc[idx].wt;

            printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[idx].pid, proc[idx].at, proc[idx].bt, proc[idx].ct, proc[idx].tat, proc[idx].wt);
        } else {
            curTime++;
        }
    }



    printf("\nAvg Waiting Time: %.2f", waitTime/ n);
    printf("\nAvg Turnaround Time: %.2f\n", avgTime / n);
}
