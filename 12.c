The **Optimal Page Replacement** algorithm replaces the page that will not be used for the longest period of time in the future. This algorithm is theoretical and serves as a benchmark for other page replacement algorithms.

Here’s a C program implementing the Optimal page replacement algorithm with a minimum frame size of three:

### C Program: Optimal Page Replacement Algorithm

```c
#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int pages[MAX_PAGES]; // Array to hold the pages
int frames[MAX_FRAMES]; // Array to hold the frames
int pageFaults = 0; // Counter for page faults

// Function to check if a page is in frames
int isPageInFrames(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return 1; // Page is found in frames
        }
    }
    return 0; // Page not found in frames
}

// Function to find the optimal page to replace
int findOptimalPage(int pages[], int n, int currentIndex) {
    int farthest = -1; // Index of the farthest page
    int pageIndex = -1; // Page index to be replaced

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                // If the page is found in the future
                if (j > farthest) {
                    farthest = j; // Update the farthest reference
                    pageIndex = i; // Update the page index to replace
                }
                break;
            }
        }
        // If the page is not found in the future
        if (j == n) {
            return i; // Replace this page
        }
    }
    return pageIndex; // Return the page index to be replaced
}

// Function to display the frames
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

// Function to implement Optimal Page Replacement
void optimalPageReplacement(int pages[], int n) {
    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Set frames to empty
    }

    for (int i = 0; i < n; i++) {
        printf("Processing page: %d\n", pages[i]);

        // If page is not in frames, we have a page fault
        if (!isPageInFrames(pages[i])) {
            pageFaults++;

            // If there's an empty frame, use it
            int emptyFrameIndex = -1;
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    emptyFrameIndex = j;
                    break;
                }
            }

            // If there is an empty frame, use it
            if (emptyFrameIndex != -1) {
                frames[emptyFrameIndex] = pages[i];
            } else {
                // Replace the optimal page
                int optimalIndex = findOptimalPage(pages, n, i + 1);
                frames[optimalIndex] = pages[i];
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
        scanf("%d", &pages[i]);
    }

    // Perform optimal page replacement
    optimalPageReplacement(pages, n);

    // Output the number of page faults
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
```

### Explanation:

1. **Data Structures**:
   - `pages[]`: Holds the page numbers that need to be loaded.
   - `frames[]`: Holds the pages currently in frames (physical memory).
   - `pageFaults`: Counts the total number of page faults.

2. **Functions**:
   - **`isPageInFrames(int page)`**: Checks if a page is currently loaded in frames.
   - **`findOptimalPage(int pages[], int n, int currentIndex)`**: Determines which page in frames should be replaced based on future references.
   - **`displayFrames()`**: Displays the current contents of the frames.
   - **`optimalPageReplacement(int pages[], int n)`**: Implements the Optimal page replacement algorithm:
     - For each page, it checks if it’s already in frames.
     - If not, it incurs a page fault and either loads it into an empty frame or replaces the optimal page if all frames are full.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `optimal_page_replacement.c`).

2. **Compile the code**:
   ```bash
   gcc optimal_page_replacement.c -o optimal_page_replacement
   ```

3. **Run the program**:
   ```bash
   ./optimal_page_replacement
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
Current frames: 2 0 3 
Processing page: 0 already in frames, no page fault.
Processing page: 4
Current frames: 2 4 3 
Processing page: 2 already in frames, no page fault.
Processing page: 3 already in frames, no page fault.
Total number of page faults: 6
```

### Explanation of Output:
- The program processes each page number and shows the current frames after each page fault.
- The total number of page faults at the end indicates how many times a page was not found in the frames.

This implementation effectively demonstrates the Optimal page replacement algorithm, which can serve as a benchmark for evaluating the performance of other page replacement algorithms.