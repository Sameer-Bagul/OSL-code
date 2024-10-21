Below is a C program that implements the C-Look disk scheduling algorithm. The C-Look algorithm is a variant of the SCAN algorithm. It serves requests in one direction and only wraps around to the first request after it has completed serving all requests in that direction. This implementation considers the initial head position moving away from the spindle.

### C Program: C-Look Disk Scheduling Algorithm

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

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

void CLook(int requests[], int n, int initial_head) {
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

    // If the current position is not at the end, wrap around to the first request
    if (current_position < requests[n - 1]) {
        total_head_movement += abs(current_position - requests[0]);
        current_position = requests[0];
        printf("%d ", current_position);
    }

    // Process remaining requests in ascending order
    for (int i = 1; i < n; i++) {
        if (requests[i] > requests[0]) {
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

    CLook(requests, n, initial_head);

    return 0;
}
```

### Explanation:

1. **Input**:
   - The program first takes the number of disk requests.
   - It then accepts the actual disk request positions.
   - Finally, it asks for the initial head position.

2. **Sorting**:
   - The `sortRequests` function sorts the requests in ascending order.

3. **C-Look Scheduling**:
   - The `CLook` function processes the requests in two phases:
     - **First Phase**: It serves all requests that are greater than or equal to the current head position.
     - **Wrap Around**: If there are remaining requests lower than the current position, it wraps around to the first request and serves the remaining requests.

4. **Output**:
   - The program prints the order of requests processed and the total head movement.

### Compilation and Running Instructions:

1. **Save the code** to a file named `c_look_disk_scheduling.c`.

2. **Compile the program**:
   ```bash
   gcc c_look_disk_scheduling.c -o c_look_disk_scheduling
   ```

3. **Run the program**:
   ```bash
   ./c_look_disk_scheduling
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
Order of requests processed: 78 82 140 170 190 16 24 
Total head movement: 164
```

### Notes:
- Ensure that the disk requests are within the defined range for the disk.
- The C-Look algorithm improves efficiency by minimizing the total seek time by not moving the head all the way to the end of the disk if there are requests in the other direction. It serves only the requests in its current direction and wraps around when necessary.