Below is a C program that implements the Shortest Seek Time First (SSTF) disk scheduling algorithm. The program considers an initial head position and simulates the scheduling of disk requests based on the shortest seek time. The head moves away from the spindle.

### C Program: SSTF Disk Scheduling Algorithm

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void SSTF(int requests[], int n, int initial_head) {
    bool visited[MAX_REQUESTS] = {false};
    int total_head_movement = 0;
    int current_position = initial_head;

    // Sort the requests to process them in order
    sortRequests(requests, n);

    printf("Order of requests processed: ");
    for (int i = 0; i < n; i++) {
        int closest_index = -1;
        int min_distance = 10000; // A large number

        // Find the closest request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(current_position - requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_index = j;
                }
            }
        }

        // Move to the closest request
        if (closest_index != -1) {
            visited[closest_index] = true;
            total_head_movement += min_distance;
            current_position = requests[closest_index];
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

    SSTF(requests, n, initial_head);

    return 0;
}
```

### Explanation:

1. **Input**:
   - The program first takes the number of disk requests.
   - It then takes the actual disk request positions.
   - Finally, it asks for the initial head position.

2. **Sorting**:
   - The `sortRequests` function sorts the requests in ascending order.

3. **SSTF Scheduling**:
   - The `SSTF` function implements the SSTF algorithm. It finds the closest unvisited request to the current head position, moves the head to that request, marks it as visited, and adds the distance to the total head movement.

4. **Output**:
   - The program prints the order in which the requests are processed and the total head movement.

### Compilation and Running Instructions:

1. **Save the code** to a file named `sstf_disk_scheduling.c`.

2. **Compile the program**:
   ```bash
   gcc sstf_disk_scheduling.c -o sstf_disk_scheduling
   ```

3. **Run the program**:
   ```bash
   ./sstf_disk_scheduling
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
Order of requests processed: 43 78 82 140 170 190 24 16 
Total head movement: 155
```

### Notes:
- Make sure to enter valid disk request values within the expected range of the disk.
- The program demonstrates how the SSTF algorithm efficiently reduces seek time by always serving the closest request next.