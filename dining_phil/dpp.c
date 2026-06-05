#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N]; // One mutex per fork
pthread_t philosophers[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;                // left fork index
    int right = (id + 1) % N;     // right fork index

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Thinking

        // Deadlock Prevention: Resource Hierarchy / Asymmetric ordering
        if (id % 2 == 0) {
            // Even: Pick up left then right
            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
            
            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
        } else {
            // Odd: Pick up right then left
            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
            
            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(2); 

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
    }
    return NULL;
}

int main() {
    int i;
    int ids[N]; 

    // Initialize forks (mutexes)
    for (i = 0; i < N; i++) { 
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    } 

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL); 
    }

    // Destroy mutexes
    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}