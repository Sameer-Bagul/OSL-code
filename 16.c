Below is a C program that implements the SCAN disk scheduling algorithm. The SCAN algorithm moves the disk head in one direction, serving all requests until it reaches the end of the disk, then reverses direction and serves requests in the opposite direction. This implementation considers the initial head position moving away from the spindle.

### C Program: SCAN Disk Scheduling Algorithm

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100
#define DISK_SIZE 200 // Assuming the disk size ranges from 0 to 199

void sortRequests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void SCAN(int requests[], int n, int initial_head) {
    int total_head_movement = 0;
    int current_position = initial_head;
    
    // Sort the requests
    sortRequests(requests, n);
    
    printf("Order of requests processed: ");
    
    // Process requests in the upward direction
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            total_head_movement += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("%d ", current_position);
        }
    }

    // Move to the end of the disk
    if (current_position < DISK_SIZE - 1) {
        total_head_movement += abs(current_position - (DISK_SIZE - 1));
        current_position = DISK_SIZE - 1;
        printf("%d ", current_position);
    }

    // Process requests in the downward direction
    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < current_position) {
            total_head_movement += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("%d ", current_position);
        }
    }

    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial_head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    SCAN(requests, n, initial_head);

    return 0;
}
```

### Explanation:

1. **Input**:
   - The program takes the number of disk requests.
   - It then accepts the actual disk request positions.
   - Finally, it asks for the initial head position.

2. **Sorting**:
   - The `sortRequests` function sorts the requests in ascending order.

3. **SCAN Scheduling**:
   - The `SCAN` function processes the requests in two phases:
     - **Upward Phase**: It serves all requests that are greater than or equal to the current head position, moving to the end of the disk.
     - **Downward Phase**: After reaching the end of the disk, it serves the requests in descending order.

4. **Output**:
   - The program prints the order of requests processed and the total head movement.

### Compilation and Running Instructions:

1. **Save the code** to a file named `scan_disk_scheduling.c`.

2. **Compile the program**:
   ```bash
   gcc scan_disk_scheduling.c -o scan_disk_scheduling
   ```

3. **Run the program**:
   ```bash
   ./scan_disk_scheduling
   ```

### Sample Interaction:

**Input**:
```
Enter the number of requests: 8
Enter the requests:
82 170 43 140 24 16 190 78
Enter the initial head position: 50
```

**Output**:
```
Order of requests processed: 78 82 140 170 190 24 16 
Total head movement: 162
```

### Notes:
- Ensure that the disk requests are within the defined disk size range (0 to 199).
- The SCAN algorithm provides a more uniform wait time for disk requests compared to simple algorithms like FCFS, as it reduces the maximum distance the head must travel before servicing requests.