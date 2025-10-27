CC = gcc
CFLAGS = 

PROGS = sample_program SJF FCFS MLFQ

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@


RUNS = 15
N = 100000000 1000000000 10000000000
NUM_THREADS = 2 4 8
NUM_TASKS = 2 4 8

run_sample_program:	sample_program
	./sample_program

run_SJF:	SJF
	./SJF

run_FCFS:

run_MLFQ:

clean:
	rm -f $(PROGS) *.o
