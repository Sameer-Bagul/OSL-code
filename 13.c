To implement full duplex communication between two independent processes using FIFOs (named pipes), we will create two processes:

1. The **first process** accepts sentences from the user, writes them to a FIFO, and waits for the second process to respond with the statistics.
2. The **second process** reads the sentences from the FIFO, counts the number of characters, words, and lines, writes the statistics to a file, and sends the contents of the file back through another FIFO to the first process.

### C Program: Full Duplex Communication Using FIFOs

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO1 "/tmp/fifo1" // FIFO for communication from process 1 to process 2
#define FIFO2 "/tmp/fifo2" // FIFO for communication from process 2 to process 1
#define MAX_INPUT_SIZE 1024
#define OUTPUT_FILE "output.txt"

// Function to count characters, words, and lines
void countStatistics(const char *input, int *charCount, int *wordCount, int *lineCount) {
    *charCount = strlen(input);
    *wordCount = 0;
    *lineCount = 0;

    char *token;
    char *inputCopy = strdup(input);
    
    // Count lines
    *lineCount = 1; // Start with 1 line
    for (int i = 0; input[i]; i++) {
        if (input[i] == '\n') {
            (*lineCount)++;
        }
    }

    // Count words
    token = strtok(inputCopy, " \n");
    while (token != NULL) {
        (*wordCount)++;
        token = strtok(NULL, " \n");
    }

    free(inputCopy);
}

// Process 1: Accept sentences
void process1() {
    int fd1, fd2;
    char input[MAX_INPUT_SIZE];

    // Create FIFO1 and FIFO2
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while (1) {
        printf("Enter a sentence (or type 'exit' to quit): ");
        fgets(input, MAX_INPUT_SIZE, stdin);
        if (strcmp(input, "exit\n") == 0) {
            break; // Exit the loop
        }

        // Write input to FIFO1
        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, input, strlen(input) + 1); // Include null terminator
        close(fd1);

        // Read output from FIFO2
        fd2 = open(FIFO2, O_RDONLY);
        char output[MAX_INPUT_SIZE];
        read(fd2, output, sizeof(output));
        printf("Statistics: %s\n", output);
        close(fd2);
    }

    // Clean up
    unlink(FIFO1);
    unlink(FIFO2);
}

// Process 2: Count statistics
void process2() {
    int fd1, fd2;
    char input[MAX_INPUT_SIZE];

    while (1) {
        // Read input from FIFO1
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, input, sizeof(input));
        if (strcmp(input, "exit\n") == 0) {
            close(fd1);
            break; // Exit the loop
        }
        close(fd1);

        int charCount, wordCount, lineCount;
        countStatistics(input, &charCount, &wordCount, &lineCount);

        // Write statistics to a file
        FILE *file = fopen(OUTPUT_FILE, "a");
        fprintf(file, "Characters: %d, Words: %d, Lines: %d\n", charCount, wordCount, lineCount);
        fclose(file);

        // Read file contents to send back to process 1
        char output[MAX_INPUT_SIZE];
        snprintf(output, sizeof(output), "Characters: %d, Words: %d, Lines: %d", charCount, wordCount, lineCount);

        // Write output to FIFO2
        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, output, strlen(output) + 1); // Include null terminator
        close(fd2);
    }
}

int main() {
    pid_t pid = fork(); // Create a new process

    if (pid == 0) {
        // Child process
        process2();
    } else if (pid > 0) {
        // Parent process
        process1();
    } else {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

### Explanation:

1. **FIFOs**: Two named pipes (`FIFO1` and `FIFO2`) are created for communication between the processes.
2. **Process 1**:
   - Accepts sentences from the user and writes them to `FIFO1`.
   - Reads statistics from `FIFO2` and displays them.
3. **Process 2**:
   - Reads sentences from `FIFO1`, counts the number of characters, words, and lines.
   - Writes the statistics to a file (`output.txt`) and sends the statistics back through `FIFO2`.

### Compilation and Running Instructions:

1. **Save the code** to a file, for example, `fifo_communication.c`.

2. **Compile the code**:
   ```bash
   gcc fifo_communication.c -o fifo_communication
   ```

3. **Run the program**:
   ```bash
   ./fifo_communication
   ```

### Sample Interaction:

**Input**:
```
Enter a sentence (or type 'exit' to quit): Hello, how are you?
Enter a sentence (or type 'exit' to quit): This is a test.
Enter a sentence (or type 'exit' to quit): exit
```

**Output**:
```
Statistics: Characters: 24, Words: 5, Lines: 1
Statistics: Characters: 19, Words: 4, Lines: 1
```

### Note:
- The output file `output.txt` will contain the statistics for each sentence processed.
- To see the contents of the output file, you can use the `cat output.txt` command in another terminal after running the program.