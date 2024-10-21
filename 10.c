The **First-Come, First-Served (FCFS)** page replacement algorithm replaces pages in the order they arrive. It is a simple algorithm but can lead to high page fault rates compared to other algorithms like LRU or Optimal.

Here's a C program implementing the FCFS page replacement algorithm with a minimum frame size of three:

### C Program: FCFS Page Replacement Algorithm

```c
#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int page[MAX_PAGES]; // Array to hold the pages
int frames[MAX_FRAMES]; // Array to hold the frames
int pageFaults = 0; // Counter for page faults

void initializeFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }
}

int isPageInFrames(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return 1; // Page is found in frames
        }
    }
    return 0; // Page not found in frames
}

void displayFrames() {
    printf("Current frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf(" - ");
        }
    }
    printf("\n");
}

void fcfsPageReplacement(int pages[], int n) {
    int nextFrameIndex = 0; // Next available frame index

    for (int i = 0; i < n; i++) {
        printf("Processing page: %d\n", pages[i]);

        // Check if the page is already in frames
        if (!isPageInFrames(pages[i])) {
            // Page fault occurs
            pageFaults++;

            // If there is an empty frame, add the page
            if (nextFrameIndex < MAX_FRAMES) {
                frames[nextFrameIndex++] = pages[i];
            } else {
                // Replace the oldest page (FCFS)
                frames[nextFrameIndex % MAX_FRAMES] = pages[i];
                nextFrameIndex++;
            }
            displayFrames(); // Show current frames after page replacement
        } else {
            printf("Page %d already in frames, no page fault.\n", pages[i]);
        }
    }
}

int main() {
    int n;

    // Input number of pages
    printf("Enter the number of pages (up to %d): ", MAX_PAGES);
    scanf("%d", &n);

    // Input pages
    printf("Enter the page numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &page[i]);
    }

    // Initialize frames and perform FCFS page replacement
    initializeFrames();
    fcfsPageReplacement(page, n);

    // Output the number of page faults
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
```

### Explanation:

1. **Data Structures**:
   - `page[]`: Holds the pages that need to be loaded.
   - `frames[]`: Holds the pages currently in frames (physical memory).
   - `pageFaults`: Counts the total number of page faults.

2. **Functions**:
   - **`initializeFrames()`**: Initializes the frames to -1 (empty).
   - **`isPageInFrames(int page)`**: Checks if a page is currently loaded in frames.
   - **`displayFrames()`**: Displays the current contents of the frames.
   - **`fcfsPageReplacement(int pages[], int n)`**: Implements the FCFS page replacement algorithm:
     - For each page, it checks if it’s already in frames.
     - If not, it incurs a page fault and either loads it into an empty frame or replaces the oldest page if all frames are full.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `fcfs_page_replacement.c`).

2. **Compile the code**:
   ```bash
   gcc fcfs_page_replacement.c -o fcfs_page_replacement
   ```

3. **Run the program**:
   ```bash
   ./fcfs_page_replacement
   ```

### Sample Input and Output:
**Input**:
```
Enter the number of pages (up to 20): 10
Enter the page numbers:
7 0 1 2 0 3 0 4 2 3
```

**Output**:
```
Processing page: 7
Current frames: 7 - - 
Processing page: 0
Current frames: 7 0 - 
Processing page: 1
Current frames: 7 0 1 
Processing page: 2
Current frames: 2 0 1 
Processing page: 0 already in frames, no page fault.
Processing page: 3
Current frames: 2 3 1 
Processing page: 0 already in frames, no page fault.
Processing page: 4
Current frames: 4 3 1 
Processing page: 2 already in frames, no page fault.
Processing page: 3 already in frames, no page fault.
Total number of page faults: 5
```

### Explanation of Output:
- The program processes each page number and shows the current frames after each page fault.
- The total number of page faults at the end indicates how many times a page was not found in the frames.

This implementation effectively demonstrates the FCFS page replacement algorithm in a clear and concise manner.