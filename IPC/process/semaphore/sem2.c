#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semutil.h"

int main(int argc, char *argv[])
{
	int i;
	sem_id = semget((key_t) 1234, 1, 0666 | IPC_CREAT);
	int pid = fork();
	if (pid != 0) {
		if (!set_semvalue()) {
			printf("Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
		printf("\nsemaphore initialised\n");
		//sleep(1);
	}
	for(i = 0; i < 5; i++) {
		if (!down()) 
			exit(EXIT_FAILURE);
		if(pid == 0){printf("Child it: %d\n",i);}
		else {printf("Parent it: %d\n",i);}
		printf("hello");
		fflush(stdout);
		sleep(2); // To switch between parent child. otherwise, executes in one go.
		printf("world -critical\n");
		fflush(stdout);
		if (!up()) 
			exit(EXIT_FAILURE);		
	}
	printf("\n%d - finished\n", getpid());
	if (pid != 0) {
		printf("Parent sleeping...");
		sleep(2);
		del_semvalue();
	}
	exit(EXIT_SUCCESS);
}
