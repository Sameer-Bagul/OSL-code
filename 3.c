// Implement the C program in which main program accepts the integers to be sorted. Main 
// program uses the FORK system call to create a new process called a child process. Parent 
// process sorts the integers using sorting algorithm and waits for child process using WAIT 
// system call to sort the integers using any sorting algorithm. Also demonstrate orphan state. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Bubble sort function
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to display the array
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    // Get number of integers to be sorted
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    int childArr[n];

    // Input integers
    printf("Enter integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        childArr[i] = arr[i]; // Copy array for child process
    }

    // Create a child process using fork()
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(5); // Delay to ensure parent terminates first
        printf("Child Process (Orphan): Sorting integers\n");
        bubbleSort(childArr, n);
        printf("Sorted by Child: ");
        displayArray(childArr, n);

        // Child process completes
        printf("Child Process Completed.\n");
    } else {
        // Parent process
        printf("Parent Process: Sorting integers\n");
        bubbleSort(arr, n);
        printf("Sorted by Parent: ");
        displayArray(arr, n);

        // Parent process terminates immediately, leaving the child orphaned
        printf("Parent Process: Exiting before child completes (Orphan state will occur).\n");
        exit(0);
    }

    return 0;
}
