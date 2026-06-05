#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Process {
    int pid;
    int burst;
    int period;
    int remaining;
};


int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
    }

    printf("Enter the time periods:\n");
    int hyperPeriod = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].period);
        hyperPeriod = lcm(hyperPeriod, p[i].period);
    }

    printf("\nLCM=%d\n", hyperPeriod);

    // Print process table
    printf("\nRate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].burst, p[i].period);
    }


    double U = 0.0;
    for (int i = 0; i < n; i++) {
        U += (double)p[i].burst / p[i].period;
    }
    double bound = n * (pow(2.0, 1.0/n) - 1);
    printf("\n%.6f <= %.6f => %s\n", U, bound, (U <= bound ? "true" : "false"));
    printf("Scheduling occurs for %d ms\n\n", hyperPeriod);


    for (int t = 0; t < hyperPeriod; t++) {
    	int chosen = -1;

    	// Reset remaining time at start of each period
    	for (int i = 0; i < n; i++) {
    	    if (t % p[i].period == 0) {
    	        p[i].remaining = p[i].burst;
    	    }
   	 }

   	 // Select the ready process with the shortest period
   	 int minPeriod = 1e9; // large number
   	 for (int i = 0; i < n; i++) {
   	     if (p[i].remaining > 0 && p[i].period < minPeriod) {
   	         minPeriod = p[i].period;
   	         chosen = i;
    	    }
   	 }

   	 // Run chosen process or idle
   	 if (chosen != -1) {
    	    printf("%dms onwards: Process %d running\n", t, p[chosen].pid);
            p[chosen].remaining--;
    	} else {
        	printf("%dms onwards: CPU is idle\n", t);
    	}
    }

    return 0;
}
