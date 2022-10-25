#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <semaphore.h>

pthread_t tid[2]; 
int counter; 
sem_t sem1;
sem_t sem2;

void* firstthread(void *arg) 
{ 

	while(1) {
		sem_wait(&sem1);
		unsigned long i = 0; 
		counter += 1; 
		printf("\n Thread1: Job %ld has started\n", pthread_self()); 
		sleep(1);
		sem_post(&sem2);
		}
	return NULL; 
} 
void* secondthread(void *arg) 
{ 
	while(1) {
		sem_wait(&sem2);
		unsigned long i = 0; 
		counter += 1; 
		printf("\n Thread2: Job %ld has started\n", pthread_self()); 
		sleep(1);
		sem_post(&sem1);
		}
	return NULL; 
} 


int main(void) 
{ 	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);
	int i = 0; 
	int error; 

	error = pthread_create(&(tid[i]), NULL, &firstthread, NULL); 
		if (error != 0) 
			printf("\nThread1 can't be created :[%s]", strerror(error)); 
	i++; 
	error = pthread_create(&(tid[i]), NULL, &secondthread, NULL); 
		if (error != 0) 
			printf("\nThread2 can't be created :[%s]", strerror(error));
	

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 

	return 0; 
} 

