#include <stdio.h>
#include <stdlib.h>

#define LEN 4

struct Process {
    int id, at, bt, rt, ct, wt, tat;
};

int main() {
    int completed = 0, time = 0;

    struct Process *p[LEN];

    for (int i = 0; i < LEN; i++) {
        p[i] = (struct Process *)malloc(sizeof(struct Process));

        p[i]->id = i + 1;
        printf("Enter Arrival & Burst for P%d: ", i + 1);
        scanf("%d %d", &p[i]->at, &p[i]->bt);
        p[i]->rt = p[i]->bt; // Initialize remaining time
    }

    while (completed < LEN) {
        int best = -1;

        for (int i = 0; i < LEN; i++) {
            if (p[i]->at <= time && p[i]->rt > 0) {
                if (best == -1 || p[i]->rt < p[best]->rt) {
                    best = i;
                }
            }
        }

        if (best != -1) {
            p[best]->rt--;

            if (p[best]->rt == 0) {
                completed++;
                p[best]->ct = time + 1;
                p[best]->tat = p[best]->ct - p[best]->at;
                p[best]->wt = p[best]->tat - p[best]->bt;
            }
        }
        time++;
    }

    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < LEN; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i]->id, p[i]->at, p[i]->bt, p[i]->ct, p[i]->tat, p[i]->wt);
    }

    return 0;
}
