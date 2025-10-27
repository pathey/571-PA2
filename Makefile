CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wno-unused-parameter
CLAGS_FEEDBACK = -O2 -Wall -Wextra
RUNS ?= 30
QUANTA ?=

PROGS = sample_program SJF FCFS MLFQ RR



all: $(PROGS)

all_feedback: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@



run_sample_program:	sample_program
	./sample_program

run_SJF:	SJF
	./SJF

run_FCFS:

run_MLFQ:	MLFQ
	./MLFQ

run_RR:		RR
	./RR


avg-%: %
	@echo "Averaging $* over $(RUNS) run(s) $(if $(QUANTA),with args: $(QUANTA),with no args)..."
	@for i in $$(seq 1 $(RUNS)); do ./$* $(QUANTA); done | \
	awk '{sum += $$1; count++} END {if(count>0) printf("Average: %.20f\n", sum/count)}'

avg-all: $(addprefix avg-,$(PROGRAMS))

clean:
	rm -f $(PROGS) *.o
