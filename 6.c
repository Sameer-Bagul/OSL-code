// Implement the C program for CPU Scheduling Algorithms: Round Robin with different arrival 
// time.

#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;    // Waiting time
    int finished;   // Is process finished
};

void roundRobinScheduling(struct Process p[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    int queue[n];
    int front = 0, rear = 0;
    int mark[n];

    // Initialize the mark array to keep track of processes in queue
    for (int i = 0; i < n; i++) {
        mark[i] = 0;
    }

    // Add the first process to the queue
    queue[rear++] = 0;
    mark[0] = 1;

    while (completed != n) {
        int processIndex = queue[front];
        front = (front + 1) % n;

        // Process has arrived and can be executed
        if (p[processIndex].remaining > 0) {
            if (p[processIndex].remaining > timeQuantum) {
                // If remaining time is more than the time quantum
                currentTime += timeQuantum;
                p[processIndex].remaining -= timeQuantum;
            } else {
                // If process finishes within the time quantum
                currentTime += p[processIndex].remaining;
                p[processIndex].completion = currentTime;
                p[processIndex].turnaround = p[processIndex].completion - p[processIndex].arrival;
                p[processIndex].waiting = p[processIndex].turnaround - p[processIndex].burst;
                p[processIndex].remaining = 0;
                completed++;
            }
        }

        // Add all processes that have arrived by the current time to the queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && mark[i] == 0 && p[i].remaining > 0) {
                queue[rear] = i;
                rear = (rear + 1) % n;
                mark[i] = 1;
            }
        }

        // Re-add the current process to the queue if it is not finished
        if (p[processIndex].remaining > 0) {
            queue[rear] = processIndex;
            rear = (rear + 1) % n;
        }
    }
}

void printResults(struct Process p[], int n) {
    float totalTurnaround = 0, totalWaiting = 0;

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        totalTurnaround += p[i].turnaround;
        totalWaiting += p[i].waiting;
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", p[i].pid);
        scanf("%d%d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].finished = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    // Execute Round Robin scheduling
    roundRobinScheduling(p, n, timeQuantum);

    // Display the results
    printResults(p, n);

    return 0;
}
