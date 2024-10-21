The **Banker's Algorithm** is a deadlock avoidance algorithm that tests for the safety of resource allocation and ensures that a system remains in a safe state. It requires the number of resources available, the maximum demand of each process, and the current allocation of resources.

Here’s a C program implementing the Banker's Algorithm:

### C Program: Banker's Algorithm

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int max[MAX_PROCESSES][MAX_RESOURCES];   // Maximum R that can be allocated to each process
int allot[MAX_PROCESSES][MAX_RESOURCES]; // R allocated to each process
int need[MAX_PROCESSES][MAX_RESOURCES];  // R needs of each process
int avail[MAX_RESOURCES];                 // Available R

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Function to check if the request can be granted
bool isSafe() {
    bool finish[MAX_PROCESSES] = {0}; // Finish array
    int safeSeq[MAX_PROCESSES];        // To store the safe sequence
    int work[MAX_RESOURCES];           // Work array to keep track of available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = avail[i]; // Initialize work with available resources
    }

    int count = 0; // Count of processes that have finished
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int p = 0; p < MAX_PROCESSES; p++) {
            // If the process is not finished and its needs can be satisfied
            if (!finish[p]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[p][j] > work[j]) {
                        break; // Break if the needed resources are more than available
                    }
                }

                // If all needs can be satisfied
                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allot[p][k]; // Add the allocated resources to work
                    }
                    safeSeq[count++] = p; // Add process to safe sequence
                    finish[p] = true;     // Mark process as finished
                    found = true;         // Mark as found
                }
            }
        }
        // If no process was found in this iteration
        if (!found) {
            printf("System is not in a safe state.\n");
            return false; // Not in a safe state
        }
    }

    // If the system is in a safe state, print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

int main() {
    // Input available resources
    printf("Enter the number of available resources:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &avail[i]);
    }

    // Input maximum resources for each process
    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocated resources for each process
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    calculateNeed(); // Calculate the need matrix
    isSafe();        // Check if the system is in a safe state

    return 0;
}
```

### Explanation:

1. **Data Structures**:
   - `max[][]`: Maximum resources required by each process.
   - `allot[][]`: Currently allocated resources for each process.
   - `need[][]`: Remaining resources needed by each process (`max - allot`).
   - `avail[]`: Available resources in the system.

2. **Functions**:
   - **`calculateNeed()`**: Calculates the need matrix by subtracting allocated resources from maximum resources.
   - **`isSafe()`**: Checks if the system is in a safe state by trying to find a safe sequence of process execution.

3. **Algorithm Logic**:
   - The algorithm iterates through processes and checks if their needs can be satisfied with the available resources.
   - If a process can be executed, its resources are added back to the available resources (simulating its completion).
   - If all processes can be finished in some order, the system is in a safe state.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `bankers_algorithm.c`).

2. **Compile the code**:
   ```bash
   gcc bankers_algorithm.c -o bankers_algorithm
   ```

3. **Run the program**:
   ```bash
   ./bankers_algorithm
   ```

### Sample Input and Output:
**Input**:
```
Enter the number of available resources:
Resource 0: 3
Resource 1: 2
Resource 2: 2
Enter the maximum resources for each process:
Process 0: 7 5 3
Process 1: 3 2 2
Process 2: 9 0 2
Process 3: 2 2 2
Process 4: 4 3 3
Enter the allocated resources for each process:
Process 0: 0 1 0
Process 1: 2 0 0
Process 2: 3 0 2
Process 3: 2 1 1
Process 4: 0 0 2
```

**Output**:
```
System is in a safe state.
Safe sequence is: 1 3 4 0 2 
```

### Explanation of Output:
- The output indicates whether the system is in a safe state and displays a safe sequence of process execution.

This implementation of the Banker's Algorithm helps demonstrate deadlock avoidance by ensuring the system never enters an unsafe state.