# priyanshu-negi-os-lab-manual
# Operating Systems Lab (C++)

**Course:** CEC301 / CSC301 — Operating Systems
**Programme:** B.Tech (CSE), Third Year

**Submitted by:** Priyanshu Negi
**Roll No.:** 2472171
**Submitted to:** Mrs. Yashvi Uniyal

This repository contains the programs of the Operating Systems practical file, written in C++.
The full lab file (aim, theory, code, output and viva questions) is in `OS_Lab_Manual_CPP.pdf`.

## Programs

| No. | Program | What it does |
|-----|---------|--------------|
| 1 | `01_fork_exec_wait.cpp` | Creates a child process with `fork()`, runs `ls -l` in it using `exec()`, and the parent waits with `wait()`. |
| 2 | `02_pthreads_sum.cpp` | Splits a sum of numbers across 4 POSIX threads and adds up their partial results. |
| 3 | `03_cpu_scheduling.cpp` | Simulates FCFS, SJF, Priority and Round Robin scheduling and prints average waiting and turnaround time. |
| 4 | `04_producer_consumer.cpp` | Producer-Consumer problem with a shared buffer, solved using semaphores. |
| 5 | `05_readers_writers.cpp` | Readers-Writers problem: many readers can read together, a writer needs exclusive access. |
| 6 | `06_dining_philosophers.cpp` | Dining Philosophers problem, with deadlock avoided by letting at most 4 philosophers pick up forks. |
| 7 | `07_bankers_algorithm.cpp` | Banker's Algorithm: checks if the system is in a safe state and whether a resource request can be granted. |
| 8 | `08_memory_allocation.cpp` | Allocates processes to memory blocks using First Fit, Best Fit and Worst Fit. |
| 9 | `09_page_replacement.cpp` | Counts page faults for FIFO, LRU and Optimal page replacement. |
| 10 | `10_disk_scheduling.cpp` | Calculates total head movement for FCFS, SSTF, SCAN and C-SCAN disk scheduling. |
| 11 | `11_file_allocation.cpp` | Simulates Contiguous, Linked and Indexed file allocation on a small disk. |

`sync_common.hpp` is a header file with the `Semaphore` class used by programs 4, 5 and 6.

## How to compile and run

All programs are in the `src` folder. They need a C++17 compiler (`g++`) on Linux, macOS or WSL.

```bash
make                      # compile all programs into ./bin
./bin/03_cpu_scheduling   # run any program
```

Or compile one program by hand (add `-pthread` for programs 2, 4, 5 and 6):

```bash
g++ -std=c++17 -pthread src/04_producer_consumer.cpp -o producer_consumer
./producer_consumer
```
