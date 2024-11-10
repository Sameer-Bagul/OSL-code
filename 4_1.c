// Implement the C program in which main program accepts an array. Main program uses the FORK 
// system call to create a new process called a child process. Child process sorts an array. The child 
// process uses EXECVE system call to load new program which display array in reverse order. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

// Main function
int main() {
    int n;

    // Get number of elements in the array
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Define a static array to hold elements
    int arr[100];  // Static array size (sufficient for up to 100 elements)

    // Input array elements
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create a child process using fork
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        printf("Child Process: Sorting the array.\n");
        bubbleSort(arr, n);
        printf("Sorted Array by Child: ");
        displayArray(arr, n);

        // Prepare for execve call
        // Convert the array to a string (to pass it to another program)
        // Create an array of arguments for execve
        char *args[3];
        args[0] = "./reverse";  // Path to the program (the reverse program)
        args[1] = NULL; // Terminate the argument list with NULL

        // Execute the new program using execve
        execve(args[0], args, NULL);

        // If execve fails, exit with an error
        perror("Execve failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child to complete
        printf("Parent Process: Child has completed.\n");
    }

    return 0;
}
