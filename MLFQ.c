#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#include <string.h> 
#include <time.h> 
#include <signal.h>
#include <sys/time.h>

/************************************************************************************************ 
		These DEFINE statements represent the workload size of each task and 
		the time quantum values for Round Robin scheduling for each task.
*************************************************************************************************/

#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

#define QUANTUM1 1000
#define QUANTUM2 1000
#define QUANTUM3 1000
#define QUANTUM4 1000

/************************************************************************************************ 
					DO NOT CHANGE THE FUNCTION IMPLEMENTATION
*************************************************************************************************/
void myfunction(int param){

	int i = 2;
	int j, k;

	while(i < param){
		k = i; 
		for (j = 2; j <= k; j++)
		{
			if (k % j == 0){
				k = k/j;
				j--;
				if (k == 1){
					break;
				}
			}
		}
		i++;
	}
}
/************************************************************************************************/

int main(int argc, char const *argv[])
{
	pid_t pid1, pid2, pid3, pid4;
	int running1, running2, running3, running4;

	pid1 = fork();

	if (pid1 == 0){

		myfunction(WORKLOAD1);

		exit(0);
	}
	kill(pid1, SIGSTOP);

	pid2 = fork();

	if (pid2 == 0){

		myfunction(WORKLOAD2);

		exit(0);
	}
	kill(pid2, SIGSTOP);

	pid3 = fork();

	if (pid3 == 0){

		myfunction(WORKLOAD3);

		exit(0);
	}
	kill(pid3, SIGSTOP);

	pid4 = fork();

	if (pid4 == 0){

		myfunction(WORKLOAD4);

		exit(0);
	}
	kill(pid4, SIGSTOP);

	/************************************************************************************************ 
		At this point, all  newly-created child processes are stopped, and ready for scheduling.
	*************************************************************************************************/



	/************************************************************************************************
		- Scheduling code starts here
		- Below is a sample schedule. (which scheduling algorithm is this?)
		- For the assignment purposes, you have to replace this part with the other scheduling methods 
		to be implemented.
	************************************************************************************************/
	int quantum [4] = {1000, 1000, 1000, 1000};

	if (argc >= 2) quantum[0] = atoi(argv[1]);
	if (argc >= 3) quantum[1] = atoi(argv[2]);
	if (argc >= 4) quantum[2] = atoi(argv[3]);
	if (argc >= 5) quantum[3] = atoi(argv[4]);

	struct Process {
		pid_t pid;
		int quantum;
		int queue;
		int semaphore;
	};

	struct Process procs[4] = {
		{pid1, quantum[0], 1, 1},
		{pid2, quantum[1], 1, 1},
		{pid3, quantum[2], 1, 1},
		{pid4, quantum[3], 1, 1}
	};
	
	int queue1 = 4;
	int queue2 = 0;

	struct timespec start [4];
	struct timespec end [4];
	
	struct timespec t0;
	clock_gettime(CLOCK_MONOTONIC, &t0);
	for(int i = 0; i < 4; i++){
		start[i] = t0;
	}
	

	while (procs[0].semaphore > 0 || procs[1].semaphore > 0 || procs[2].semaphore > 0 || procs[3].semaphore > 0)
	{
		while (queue1 > 0){
			if (procs[0].semaphore > 0){
				kill(pid1, SIGCONT);
				usleep(quantum[0]);
				kill(pid1, SIGSTOP);	
			}
			if (procs[1].semaphore > 0){
				kill(pid2, SIGCONT);
				usleep(quantum[1]);
				kill(pid2, SIGSTOP);
			}
			if (procs[2].semaphore > 0){
				kill(pid3, SIGCONT);
				usleep(quantum[2]);
				kill(pid3, SIGSTOP);
			}
			if (procs[3].semaphore > 0){
				kill(pid4, SIGCONT);
				usleep(quantum[3]);
				kill(pid4, SIGSTOP);
			}
			waitpid(pid1, &procs[0].semaphore, WNOHANG);
			waitpid(pid2, &procs[1].semaphore, WNOHANG);
			waitpid(pid3, &procs[2].semaphore, WNOHANG);
			waitpid(pid4, &procs[3].semaphore, WNOHANG);
			for(int i  = 0; i < 4; i++){
				queue1--;
				if(procs[i].semaphore == 0){
					 clock_gettime(CLOCK_MONOTONIC, &end[i]);
				}
				else{
					procs[i].queue = 2;
					queue2++;
				}
			}
		}
		while(queue2 > 0){
			for(int i = 0; i < 4; i++){
				if (procs[i].semaphore == 1){
					kill(procs[i].pid, SIGCONT);
					waitpid(procs[i].pid, &procs[i].semaphore, 0);
					clock_gettime(CLOCK_MONOTONIC, &end[i]);
					queue2--;
				}
			}
		}			
	}

	for(int i = 0; i < 4; i++){
		double elapsed = (double)(end[i].tv_sec - start[i].tv_sec) + (double)(end[i].tv_nsec - start[i] .tv_nsec) / 1e9;
		printf("%.20f\n", elapsed);
	}

	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/

	return 0;
}
