#include <stdio.h>
//FCFS Algorithm
//Input - List of processes (PID, AT, BT)
//Output - CT, TAT, WT



 struct Process{
        int pid;
        int at;
        int bt;
        int ct;
        int tat;
        int wt;
    };

void main(){
    int n, i,j;
    struct Process proc[10], temp;
    int curTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    float avgTime=0.0, waitTime=0.0;
    for (i=0;i<n;i++){
        printf("Enter Arrival and Burst Times for P%d: ", i+1);
        proc[i].pid = i+1;
        scanf("%d %d", &proc[i].at, &proc[i].bt);
    }

    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
                if(proc[j].at>proc[j+1].at){
                    temp = proc[j];
                    proc[j]=proc[j+1];
                    proc[j+1]=temp;
                    proc[j+1]=temp;
        }
    }
}

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0; i<n; i++){
        if(curTime < proc[i].at) {
            curTime = proc[i].at;
        }

        proc[i].ct = curTime + proc[i].bt;
        proc[i].tat = proc[i].ct - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        curTime = proc[i].ct;

        avgTime += proc[i].tat;
        waitTime += proc[i].wt;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }



    printf("\nAvg Waiting Time: %.2f", waitTime/ n);
    printf("\nAvg Turnaround Time: %.2f\n", avgTime / n);
}
