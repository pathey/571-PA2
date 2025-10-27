PA #2

SJF.c is the shortest job first implementation, FCFS.c is the first come first serve implementation, and MLFQ.c is the multi-level feedback queue implementation.

To compile all programs run "make all". Warnings are intended to be suppressed, but had trouble implementing.

You can also run "make clean" to clear executables.

To run a given file type "make run\_\[PROGRAM NAME\]" but replace PROGRAM NAME with the name of the program excluding the ".c" suffix.

We also built the ability to quickly compute the average response time by running "make avg\-\[PROGRAM NAME\]" once again replacing PROGRAM NAME with the appropriate name without ".c"

Finally we have "make avgq\-PROGRAM NAME"  which calculates the average response time for a set of preprogrammed quanta.
