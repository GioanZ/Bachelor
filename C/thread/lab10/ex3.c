#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

sem_t s1, s2;

void *tf1(void *argc){
	while(1){
		sem_wait(&s1);
		printf("Funzione 1, con tID: %ld\n", pthread_self());
		sleep(1);
		sem_post(&s2);
	}
}
void *tf2(void *argc){
	while(1){
		sem_wait(&s2);
		printf("Funzione 2, con tID: %ld\n", pthread_self());
		sleep(1);
		sem_post(&s1);
	}
}

int main(int argc, char **argv){// gcc ex3.c -o ex3P -lpthread -lrt
	//	./ex3P
	
	pthread_t t1, t2;
	
	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 0);
	
	if(pthread_create(&t1, NULL, tf1, NULL)){
		printf("Errore creare 1\n");
	}
	if(pthread_create(&t2, NULL, tf2, NULL)){
		printf("Errore creare 2\n");
	}
	printf("creato tID: %ld\n", t1);
	printf("creato tID: %ld\n", t2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}


