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

sem_t semB, semC, semD, semE, semF, semG, semH, semI;

void *tA(){
	printf("  A\n");
	sem_post(&semB);
	sem_post(&semC);
	sem_post(&semD);
	
	pthread_exit(NULL);
}
void *tB(){
	sem_wait(&semB); 
	printf("B");
	sem_post(&semI);
	
	pthread_exit(NULL);
}
void *tC(){
	sem_wait(&semC);
	sleep(1);
	printf(" C ");
	sem_post(&semE);
	sem_post(&semF);
	
	pthread_exit(NULL);
}
void *tD(){
	sem_wait(&semD);
	sleep(2);
	printf("D\n");
	sem_post(&semH);
	
	pthread_exit(NULL);
}
void *tE(){
	sem_wait(&semE);
	sleep(3);
	printf(" E ");
	sem_post(&semG);
	
	pthread_exit(NULL);
}
void *tF(){
	sem_wait(&semF);
	sleep(4);
	printf("F\n");
	sem_post(&semG);
	
	pthread_exit(NULL);
}
void *tG(){
	sem_wait(&semG); 
	sem_wait(&semG);
	sleep(1); 
	printf("  G");
	sem_post(&semH);
	sem_post(&semI);
	
	pthread_exit(NULL);
}
void *tH(){
	sem_wait(&semH);
	sem_wait(&semH);
	printf(" H\n");
	sem_post(&semI);
	
	pthread_exit(NULL);
}
void *tI(){
	sem_wait(&semI); 
	sem_wait(&semI); 
	sem_wait(&semI); 
	sleep(1); 
	printf("  I\n");
	
	pthread_exit(NULL);
}


int main(int argc, char **argv){// gcc ex1.c -o ex1P -lpthread -lrt
	//	./ex1P
	int i=0;
	sem_init(&semB, 0, 0); 
	sem_init(&semC, 0, 0); 
	sem_init(&semD, 0, 0);
	sem_init(&semE, 0, 0);
	sem_init(&semF, 0, 0);
	sem_init(&semG, 0, 0);
	sem_init(&semH, 0, 0);
	sem_init(&semI, 0, 0);
	pthread_t t[9];
	
	
	if(pthread_create(&t[i],NULL,&tA,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tB,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tC,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tD,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tE,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tF,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tG,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,&tH,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	i++;
	if(pthread_create(&t[i],NULL,tI,NULL)){
		printf("Errore nel thread %d\n", i);
	}
	//printf("%d\n", i);
	
	for(i=0;i<9;i++){
		pthread_join(t[i], NULL);
	}
	sem_destroy(&semB); 
	sem_destroy(&semC); 
	sem_destroy(&semD); 
	sem_destroy(&semE); 
	sem_destroy(&semF); 
	sem_destroy(&semG);
	sem_destroy(&semH);
	sem_destroy(&semI); 
	
	
	return 0;
}
