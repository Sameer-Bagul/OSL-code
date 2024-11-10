#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to display the array in reverse order
void displayReverseArray(int arr[], int n) {
    printf("Array in Reverse Order: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No array passed to reverse program.\n");
        return 1;
    }

    // The arguments passed are strings, convert them to integers
    int n = argc - 1;  // Number of elements passed
    int arr[n];

    // Convert string arguments to integers
    for (int i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]);
    }

    // Display the array in reverse order
    displayReverseArray(arr, n);

    return 0;
}
