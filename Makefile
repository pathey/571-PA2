CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wno-unused-parameter
CLAGS_FEEDBACK = -O2 -Wall -Wextra

PROGS = sample_program SJF FCFS MLFQ

all: $(PROGS)

all_feedback: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@


RUNS = 15
N = 100000000 1000000000 10000000000

run_sample_program:	sample_program
	./sample_program

run_SJF:	SJF
	./SJF

run_FCFS:

run_MLFQ:	MLFQ
	./MLFQ

clean:
	rm -f $(PROGS) *.o
