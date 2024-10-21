The **Reader-Writer Problem** involves synchronization between reader and writer threads to a shared data structure (critical section). Multiple readers can read the shared resource simultaneously, but if a writer is writing, no other reader or writer can access the resource until the writer is done.

### C Program: Reader-Writer Problem Using Mutex

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;        // Mutex for mutual exclusion
pthread_mutex_t wrt;          // Mutex for writer access
int read_count = 0;           // Counter for number of readers in the critical section
int data = 0;                 // Shared data (critical section)

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        // Reader acquires access
        pthread_mutex_lock(&mutex);
        read_count++; // Increment the reader count

        // If this is the first reader, lock the writer access
        if (read_count == 1)
            pthread_mutex_lock(&wrt);
        pthread_mutex_unlock(&mutex);

        // Reading the data (critical section)
        printf("Reader %d reads the data: %d\n", reader_id, data);

        // Reader releases access
        pthread_mutex_lock(&mutex);
        read_count--; // Decrement the reader count

        // If this is the last reader, unlock the writer access
        if (read_count == 0)
            pthread_mutex_unlock(&wrt);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate reading time
    }
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        // Writer locks the writer mutex to get exclusive access
        pthread_mutex_lock(&wrt);

        // Writing the data (critical section)
        data++;
        printf("Writer %d writes the data: %d\n", writer_id, data);

        // Writer unlocks the writer mutex
        pthread_mutex_unlock(&wrt);

        sleep(2); // Simulate writing time
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, w1, w2; // Reader and writer threads
    int reader_id1 = 1, reader_id2 = 2;
    int writer_id1 = 1, writer_id2 = 2;

    // Initialize the mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    // Create reader and writer threads
    pthread_create(&r1, NULL, reader, &reader_id1);
    pthread_create(&r2, NULL, reader, &reader_id2);
    pthread_create(&w1, NULL, writer, &writer_id1);
    pthread_create(&w2, NULL, writer, &writer_id2);

    // Wait for the threads to complete (in this case, infinite loop, so won't actually terminate)
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    // Destroy the mutexes (this will not be reached in the infinite loop)
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);

    return 0;
}
```

### Explanation:

1. **Mutexes**:
   - `mutex`: Controls access to the shared `read_count` variable.
   - `wrt`: Controls exclusive access to the shared data (critical section) by writers.
   
2. **Reader Logic**:
   - Increment the `read_count` and if it's the first reader, lock the `wrt` mutex to block writers.
   - Read the shared data.
   - Decrement the `read_count` and if it's the last reader, unlock the `wrt` mutex to allow writers.
   
3. **Writer Logic**:
   - Lock the `wrt` mutex for exclusive access to the shared data.
   - Modify the shared data.
   - Unlock the `wrt` mutex to allow readers or other writers.

### Steps to Compile and Run the Code:

1. **Save the file** (e.g., `reader_writer.c`).

2. **Compile the code**:
   ```bash
   gcc reader_writer.c -o reader_writer -lpthread
   ```

3. **Run the program**:
   ```bash
   ./reader_writer
   ```

### Sample Output:
```
Reader 1 reads the data: 0
Reader 2 reads the data: 0
Writer 1 writes the data: 1
Reader 1 reads the data: 1
Reader 2 reads the data: 1
Writer 2 writes the data: 2
```

### Explanation of Output:
- Readers read the current value of the shared data.
- Writers modify the shared data, and only one writer is allowed at a time.
- Multiple readers can access the shared data simultaneously if no writer is writing.

This solution ensures mutual exclusion for writers and allows multiple readers to read the data concurrently when no writer is active, solving the Reader-Writer problem with thread synchronization using mutexes.