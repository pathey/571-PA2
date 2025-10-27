CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wno-unused-parameter
CLAGS_FEEDBACK = -O2 -Wall -Wextra
RUNS ?= 30
QUANTA ?= 100 200 300 400 500

PROGS = sample_program SJF FCFS MLFQ RR



all: $(PROGS)

all_feedback: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@



run_sample_program:	sample_program
	./sample_program

run_SJF:	SJF
	./SJF

run_FCFS:	FCFS
	./FCFS

run_MLFQ:	MLFQ
	./MLFQ

run_RR:		RR
	./RR


avg-%:
	@total=0; \
	for i in $$(seq 1 $(RUNS)); do \
		val=$$(./$*); \
		echo "Run $$i: $$val"; \
		total=$$(echo "$$total + $$val" | bc -l); \
	done; \
	avg=$$(echo "$$total / $(RUNS)" | bc -l); \
	echo "Average: $$avg"

avgq-%:
	@for q in $(QUANTA); do \
		total=0; \
		for i in $$(seq 1 $(RUNS)); do \
			val=$$(./$* $$q $$q $$q $$q); \
			total=$$(echo "$$total + $$val" | bc -l); \
		done; \
		avg=$$(echo "$$total / $(RUNS)" | bc -l); \
		printf "%s q=%s average=%s\n" "$*" "$$q" "$$avg"; \
	done

avg-all: $(addprefix avg-,$(PROGRAMS))

clean:
	rm -f $(PROGS) *.o
