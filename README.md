# Project Title

This repository contains various C programs demonstrating different concepts and algorithms in operating systems.

## Table of Contents

1. [Address Book Program](#1-address-book-program)
2. [Sorting Integers with FORK and WAIT](#2-sorting-integers-with-fork-and-wait)
3. [Sorting Integers with FORK and Orphan State](#3-sorting-integers-with-fork-and-orphan-state)
4. [Sorting Array with FORK and EXECVE](#4-sorting-array-with-fork-and-execve)
5. [CPU Scheduling: Shortest Job First (Preemptive)](#5-cpu-scheduling-shortest-job-first-preemptive)
6. [CPU Scheduling: Round Robin](#6-cpu-scheduling-round-robin)
7. [Thread Synchronization: Producer-Consumer Problem](#7-thread-synchronization-producer-consumer-problem)
8. [Thread Synchronization: Reader-Writer Problem](#8-thread-synchronization-reader-writer-problem)
9. [Deadlock Avoidance: Bankers Algorithm](#9-deadlock-avoidance-bankers-algorithm)
10. [Page Replacement: FCFS](#10-page-replacement-fcfs)
11. [Page Replacement: LRU](#11-page-replacement-lru)
12. [Page Replacement: Optimal](#12-page-replacement-optimal)
13. [FIFOS: Full Duplex Communication](#13-fifos-full-duplex-communication)
14. [Client-Server with Shared Memory](#14-client-server-with-shared-memory)
15. [Disk Scheduling: SSTF](#15-disk-scheduling-sstf)
16. [Disk Scheduling: SCAN](#16-disk-scheduling-scan)
17. [Disk Scheduling: C-Look](#17-disk-scheduling-c-look)

## 1 Address Book Program

1. Write a program to implement an address book with options given below:
    - Create address book.
    - View address book.
    - Insert a record.
    - Delete a record.
    - Modify a record.
    - Exit

## 2 Sorting Integers with FORK and WAIT

2. Implement the C program in which the main program accepts the integers to be sorted. The main program uses the `FORK` system call to create a new process called a child process. The parent process sorts the integers using a sorting algorithm and waits for the child process using the `WAIT` system call to sort the integers using any sorting algorithm. Also, demonstrate the zombie state.

## 3 Sorting Integers with FORK and Orphan State

3. Implement the C program in which the main program accepts the integers to be sorted. The main program uses the `FORK` system call to create a new process called a child process. The parent process sorts the integers using a sorting algorithm and waits for the child process using the `WAIT` system call to sort the integers using any sorting algorithm. Also, demonstrate the orphan state.

## 4 Sorting Array with FORK and EXECVE

4. Implement the C program in which the main program accepts an array. The main program uses the `FORK` system call to create a new process called a child process. The child process sorts the array. The child process uses the `EXECVE` system call to load a new program which displays the array in reverse order.

## 5 CPU Scheduling: Shortest Job First (Preemptive)

5. Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive) with different arrival times.

## 6 CPU Scheduling: Round Robin

6. Implement the C program for CPU Scheduling Algorithms: Round Robin with different arrival times.

## 7 Thread Synchronization: Producer-Consumer Problem

7. Thread synchronization using counting semaphores. Application to demonstrate: producer-consumer problem with counting semaphores and mutex.

## 8 Thread Synchronization: Reader-Writer Problem

8. Thread synchronization and mutual exclusion using mutex. Application to demonstrate: Reader-Writer problem.

## 9 Deadlock Avoidance: Bankers Algorithm

9. Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

## 10 Page Replacement: FCFS

10. Implement the C program for Page Replacement Algorithms: FCFS for a frame size of at least three.

## 11 Page Replacement: LRU

11. Implement the C program for Page Replacement Algorithms: LRU for a frame size of at least three.

## 12 Page Replacement: Optimal

12. Implement the C program for Page Replacement Algorithms: Optimal for a frame size of at least three.

## 13 FIFOS: Full Duplex Communication

13. FIFOS: Full duplex communication between two independent processes. The first process accepts sentences and writes on one pipe to be read by the second process. The second process counts the number of characters, words, and lines in the accepted sentences, writes this output in a text file, and writes the contents of the file on the second pipe to be read by the first process and displayed on standard output.

## 14 Client-Server with Shared Memory

14. Write a program to demonstrate: Client and Server Programs in which the server process creates a shared memory segment and writes the message to the shared memory segment. The client process reads the message from the shared memory segment and displays it on the screen.

## 15 Disk Scheduling: SSTF

15. Implement the C program for Disk Scheduling Algorithms: SSTF considering the initial head position moving away from the spindle.

## 16 Disk Scheduling: SCAN

16. Implement the C program for Disk Scheduling Algorithms: SCAN considering the initial head position moving away from the spindle.

## 17 Disk Scheduling: C-Look

17. Implement the C program for Disk Scheduling Algorithms: C-Look considering the initial head position moving away from the spindle.
