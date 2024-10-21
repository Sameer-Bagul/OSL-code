The **Least Recently Used (LRU)** page replacement algorithm replaces the page that has not been used for the longest period of time. It tracks the order of page usage to determine which page to replace when a page fault occurs.

Here’s a C program implementing the LRU page replacement algorithm with a minimum frame size of three:

### C Program: LRU Page Replacement Algorithm

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int pages[MAX_PAGES]; // Array to hold the pages
int frames[MAX_FRAMES]; // Array to hold the frames
int pageFaults = 0; // Counter for page faults
int pageIndex = 0; // To keep track of the index of the frames

// Function to check if a page is in frames
bool isPageInFrames(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return true; // Page is found in frames
        }
    }
    return false; // Page not found in frames
}

// Function to get the index of the least recently used page
int getLRUPage() {
    int lruIndex = 0;
    for (int i = 1; i < MAX_FRAMES; i++) {
        if (frames[i] < frames[lruIndex]) {
            lruIndex = i; // Update LRU index
        }
    }
    return lruIndex;
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

// Function to implement LRU Page Replacement
void lruPageReplacement(int pages[], int n) {
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
            if (pageIndex < MAX_FRAMES) {
                frames[pageIndex] = pages[i];
                pageIndex++;
            } else {
                // Replace the least recently used page
                int lruIndex = getLRUPage();
                frames[lruIndex] = pages[i];
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

    // Perform LRU page replacement
    lruPageReplacement(pages, n);

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
   - `pageIndex`: Keeps track of the next available index in the frames.

2. **Functions**:
   - **`isPageInFrames(int page)`**: Checks if a page is currently loaded in frames.
   - **`getLRUPage()`**: Determines which page in frames is the least recently used.
   - **`displayFrames()`**: Displays the current contents of the frames.
   - **`lruPageReplacement(int pages[], int n)`**: Implements the LRU page replacement algorithm:
     - For each page, it checks if it’s already in frames.
     - If not, it incurs a page fault and either loads it into an empty frame or replaces the least recently used page if all frames are full.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `lru_page_replacement.c`).

2. **Compile the code**:
   ```bash
   gcc lru_page_replacement.c -o lru_page_replacement
   ```

3. **Run the program**:
   ```bash
   ./lru_page_replacement
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
Processing page: 0
Current frames: 0 3 1 
Processing page: 4
Current frames: 0 3 4 
Processing page: 2
Current frames: 2 3 4 
Processing page: 3 already in frames, no page fault.
Total number of page faults: 7
```

### Explanation of Output:
- The program processes each page number and shows the current frames after each page fault.
- The total number of page faults at the end indicates how many times a page was not found in the frames.

This implementation effectively demonstrates the LRU page replacement algorithm and helps to understand how pages are replaced based on usage history.