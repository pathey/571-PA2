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
#define WORKLOAD2 100000
#define WORKLOAD3 100000
#define WORKLOAD4 100000

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

	running1 = 1;
	running2 = 1;
	running3 = 1;
	running4 = 1;
	
	struct Process {
		pid_t pid;
		int semaphore;
	};

	struct Process procs[4] = {
		{pid1, 1},
		{pid2, 1},
		{pid3, 1},
		{pid4, 1}
	};

	struct timespec start[4];
	struct timespec end [4];
	
	struct timespec t0;
	clock_gettime(CLOCK_MONOTONIC, &t0);
	for(int i = 0; i < 4; i++){
		start[i] = t0;
	}

	while (procs[0].semaphore > 0 || procs[1].semaphore > 0 || procs[2].semaphore > 0 || procs[3].semaphore > 0)
	{
		for(int i = 0; i <4; i++){
			if(procs[i].semaphore > 0){
				kill(procs[i].pid, SIGCONT);
				waitpid(procs[i].pid, &procs[i].semaphore, 0);
				clock_gettime(CLOCK_MONOTONIC, &end[i]);
			}
		}
	}

	double avg = 0;
	double elapsed [4] = {0};
	double sum = 0;
	for(int i = 0; i < 4; i++){
		elapsed[i] = (double)(end[i].tv_sec - start[i].tv_sec) + (double)(end[i].tv_nsec - start[i].tv_nsec) / 1e9;
		sum += elapsed[i];
	}

	avg = sum /4.0;
	printf("%.10f\n", sum);

	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/

	return 0;
}
