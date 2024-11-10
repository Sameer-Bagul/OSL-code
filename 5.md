//  Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) with 
// different arrival time.


The Shortest Job First (SJF) scheduling algorithm selects the process with the shortest burst time (execution time) to execute next. In the preemptive version (also known as **Shortest Remaining Time First**), if a new process arrives with a burst time shorter than the remaining time of the current process, the current process is preempted, and the new process is executed.

Here’s the C code to implement the **Preemptive Shortest Job First (SJF) Scheduling** algorithm with different arrival times:

### C Program for SJF (Preemptive) Scheduling Algorithm

```c
#include <stdio.h>
#include <limits.h>

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

void calculateTimes(struct Process p[], int n) {
    int completed = 0, currentTime = 0, shortestProcess;
    int minBurst = INT_MAX;
    
    while (completed != n) {
        shortestProcess = -1;
        minBurst = INT_MAX;

        // Find process with the shortest remaining burst time at the current time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
                shortestProcess = i;
            }
        }

        if (shortestProcess == -1) {
            currentTime++;
            continue;
        }

        // Process the selected shortest job
        p[shortestProcess].remaining--;
        currentTime++;

        // If the process is finished
        if (p[shortestProcess].remaining == 0) {
            p[shortestProcess].completion = currentTime;
            p[shortestProcess].turnaround = p[shortestProcess].completion - p[shortestProcess].arrival;
            p[shortestProcess].waiting = p[shortestProcess].turnaround - p[shortestProcess].burst;
            completed++;
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
    int n;

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

    // Calculate times using the SJF Preemptive Scheduling Algorithm
    calculateTimes(p, n);

    // Display the results
    printResults(p, n);

    return 0;
}
```

### Explanation:
1. **Process Structure**:
   - `pid`: Process ID.
   - `arrival`: Arrival time of the process.
   - `burst`: Burst time (execution time) of the process.
   - `remaining`: Remaining burst time (used for preemptive execution).
   - `completion`: Completion time when the process finishes.
   - `turnaround`: Turnaround time (`completion time - arrival time`).
   - `waiting`: Waiting time (`turnaround time - burst time`).
   - `finished`: A flag to mark whether the process is finished.

2. **`calculateTimes()`**:
   - Simulates the CPU scheduling by selecting the process with the shortest remaining time at each time unit.
   - Preempts the current process if a new process with a shorter burst time arrives.
   - Updates the remaining time and completes the process when `remaining == 0`.

3. **`printResults()`**:
   - Displays the results in tabular form.
   - Calculates and prints the average turnaround time and waiting time.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `sjf_preemptive.c`).

2. **Compile the code**:
   ```bash
   gcc sjf_preemptive.c -o sjf_preemptive
   ```

3. **Run the program**:
   ```bash
   ./sjf_preemptive
   ```

### Sample Input/Output:

#### Input:
```
Enter the number of processes: 3
Enter arrival time and burst time for process P1: 0 8
Enter arrival time and burst time for process P2: 1 4
Enter arrival time and burst time for process P3: 2 9
```

#### Output:
```
Process Arrival Burst Completion Turnaround Waiting
1       0      8     13         13         5
2       1      4     5          4          0
3       2      9     22         20         11

Average Turnaround Time: 12.33
Average Waiting Time: 5.33
```

### How It Works:
- The process with the shortest remaining burst time is selected at each time unit.
- When a new process arrives, it preempts the current process if the new process has a shorter burst time.
- The program tracks the waiting and turnaround times for each process and displays the results.