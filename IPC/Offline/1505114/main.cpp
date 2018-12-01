#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include <unistd.h>
#include <sys/sem.h>
#include <iostream>

#include "Cake.h"

#define CHOCOLATE 1
#define VANILLA 0
#define QUEUE_SIZE 5
#define CAKE_NO 10
using namespace std;


//semaphore to control sleep and wake up
sem_t empty;
sem_t full;

sem_t q3empty;
sem_t q3full;

sem_t q2empty;
sem_t q2full;

queue<Cake *> q1;
queue<Cake *> q2;
queue<Cake *> q3;
int i = 1; //Cake id

pthread_mutex_t lock;


void init_semaphore()
{
	sem_init(&empty,0,QUEUE_SIZE);
	sem_init(&full,0,0);
	
	sem_init(&q2empty,0,QUEUE_SIZE);
	sem_init(&q2full,0,0);
	
	sem_init(&q3empty,0,QUEUE_SIZE);
	sem_init(&q3full,0,0);
	
	pthread_mutex_init(&lock,0);
}

void * ChocolateProd(void * arg)
{	
	printf("%s\n",(char*)arg);
	
	for(int j = 0 ; j< CAKE_NO ; j++)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&lock);		
		
		q1.push(new Cake(i ,CHOCOLATE ));
		printf("Chef X produced Chocolate cake %d\n",i);
		i++;	
		sleep(1);	

		pthread_mutex_unlock(&lock);
		sem_post(&full);

	}
	printf("Chocolate Producer Exited.\n");
}


void * VanillaProd(void * arg)
{	
	printf("%s\n",(char*)arg);

	for(int j =0 ; j< CAKE_NO ; j++)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&lock);		

		q1.push(new Cake(i ,VANILLA));
		printf("Chef Y produced Vanilla cake %d\n",i);
		i++;		
		sleep(1);	

		pthread_mutex_unlock(&lock);
		sem_post(&full);
	
	}
	printf("Vanilla Producer Exited.\n");

}


void * Decorator(void * arg)
{	
	printf("%s\n",(char*)arg);
	
	// while(!q1.empty())
	for(int j = 0 ; j< 2*CAKE_NO ; j++)
	{

		sem_wait(&full);
		pthread_mutex_lock(&lock);		

		Cake * item = q1.front();
		if(item->getType() == CHOCOLATE){
			sem_wait(&q3empty);
		
			q1.pop();
			q3.push(item);
			printf("Chocolate cake moved from Q1 -> Q3 :");
	
			sem_post(&q3full);
		}
		else if (item->getType() == VANILLA)
		{
			sem_wait(&q2empty);
			q1.pop();
			q2.push(item);
			printf("Vanilla cake moved from Q1 -> Q2 :");

			sem_post(&q2full);
		}
		printf("Chef Z decorated cake %d\n",item->getID());
		sleep(1);	

		pthread_mutex_unlock(&lock);
		sem_post(&empty);
	

	}
	printf("Decorator Exited\n");
}

void * Waiter_1_Consume(void * arg)
{
	printf("%s\n",(char*)arg);

	// while(!q3.empty())
	for(int j =0 ; j< CAKE_NO ; j++)
	{	
 		sem_wait(&q3full);
		pthread_mutex_lock(&lock);

 		printf("Waiter 1 serving->\n");
			
		Cake * item = q3.front();
		q3.pop();
		printf("Waiter 1 served Cake: %d\n",item->getID());	
		sleep(1);

		pthread_mutex_unlock(&lock);
		sem_post(&q3empty);
	}
	printf("Waiter 1 exited\n");
}

void * Waiter_2_Consume(void * arg)
{
	printf("%s\n",(char*)arg);
	// while(!q2.empty())
	for(int j =0 ; j< CAKE_NO ; j++)
	{	
		sem_wait(&q2full);
		pthread_mutex_lock(&lock);

 		printf("Waiter 2 serving->\n");
			
		Cake * item = q2.front();
		q2.pop();
		printf("Waiter 2 Cake: %d\n",item->getID());	
		sleep(1);

		pthread_mutex_unlock(&lock);
		sem_post(&q2empty);
		
	}
	printf("Waiter 2 exited\n");

}




int main(void)
{	
	pthread_t chefx;
	pthread_t chefy;
	pthread_t chefz;

	pthread_t waiter1;
	pthread_t waiter2;

	
	init_semaphore();
	
	
	pthread_create(&chefx,NULL,ChocolateProd,(void*)"ChefX started..." );
	pthread_create(&chefy,NULL,VanillaProd,(void*)"ChefY started..." );
	pthread_create(&chefz,NULL,Decorator,(void*)"ChefZ started..." );

	pthread_create(&chefy,NULL,Waiter_1_Consume,(void*)"Waiter 1 started.." );
	pthread_create(&chefz,NULL,Waiter_2_Consume,(void*)"Waiter 2 started..." );
	
	while(1);
	// pthread_exit(NULL);
	return 0;
}
