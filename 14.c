Below is a C program demonstrating a client-server architecture using shared memory. The server creates a shared memory segment, writes a message to it, and the client reads the message from the shared memory segment and displays it.

### C Program: Client-Server Using Shared Memory

**Server Code (server.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    int shmid;
    char *shared_memory;
    key_t key = 1234; // Key for the shared memory segment

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    shared_memory = (char*)shmat(shmid, NULL, 0);
    if (shared_memory == (char*)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Write a message to shared memory
    printf("Server: Writing to shared memory...\n");
    strcpy(shared_memory, "Hello from the Server!");

    // Detach the shared memory segment
    shmdt(shared_memory);
    printf("Server: Message written. Waiting for client to read...\n");

    // Wait for client to read (optional)
    sleep(10);

    // Delete the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
```

**Client Code (client.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    int shmid;
    char *shared_memory;
    key_t key = 1234; // Key for the shared memory segment

    // Get the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    shared_memory = (char*)shmat(shmid, NULL, 0);
    if (shared_memory == (char*)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read the message from shared memory
    printf("Client: Reading from shared memory...\n");
    printf("Client: Message: %s\n", shared_memory);

    // Detach the shared memory segment
    shmdt(shared_memory);
    return 0;
}
```

### Explanation:

1. **Server**:
   - Creates a shared memory segment using `shmget`.
   - Attaches the shared memory segment using `shmat`.
   - Writes a message to the shared memory segment.
   - Optionally sleeps for a while to wait for the client to read the message.
   - Deletes the shared memory segment using `shmctl`.

2. **Client**:
   - Retrieves the shared memory segment using `shmget`.
   - Attaches the shared memory segment using `shmat`.
   - Reads the message from the shared memory segment and displays it.
   - Detaches the shared memory segment using `shmdt`.

### Compilation and Running Instructions:

1. **Save the server code** to a file named `server.c` and the client code to a file named `client.c`.

2. **Compile both programs**:
   ```bash
   gcc server.c -o server
   gcc client.c -o client
   ```

3. **Run the server** in one terminal:
   ```bash
   ./server
   ```

4. **Run the client** in another terminal:
   ```bash
   ./client
   ```

### Sample Interaction:

- **Server Output**:
```
Server: Writing to shared memory...
Server: Message written. Waiting for client to read...
```

- **Client Output**:
```
Client: Reading from shared memory...
Client: Message: Hello from the Server!
```

### Notes:
- Make sure to run the server before the client to ensure that the shared memory segment is created and ready for the client to read.
- The server will wait for 10 seconds before terminating to allow time for the client to read the message. You can adjust this delay or use synchronization mechanisms if needed.