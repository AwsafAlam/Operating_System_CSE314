#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semutil.h"

int main(int argc, char *argv[])
{
	int i;
	sem_id = semget((key_t) 1234, 1, 0666 | IPC_CREAT);
	if (argc > 1) {
		if (!set_semvalue()) {
			printf("Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
		printf("\nSemaphore initialised\n");
		sleep(2);
	}
	for(i = 0; i < 5; i++) {
		if (!down()) exit(EXIT_FAILURE);
		printf("hello");
		fflush(stdout);
		sleep(4);
		printf("world -critical\n");
		fflush(stdout);
		if (!up()) exit(EXIT_FAILURE);	
	}
	printf("\n%d - finished\n", getpid());
	if (argc > 1) {
		printf("Parent sleeping...");
		sleep(6);
		del_semvalue();
	}
	exit(EXIT_SUCCESS);
}
