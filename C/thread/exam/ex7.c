#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
// gcc ex7.c -o ex7 -lpthread -lrt
#define N 6

int sem=0;
sem_t s, s2, sN;

void A(){
	int i;
	for(i=0;i<10;i++){
		printf("A");
	}
	printf("\n");
}
void B(){
	int i;
	for(i=0;i<10;i++){
		printf("B");
	}
	printf("\n");
}

void *f(void *argc){
	int i;
	A();
	
	sem_post(&sN);
	sem_wait(&s);
	if(sem==0){
		sem=1;
		sem_post(&s);
		for(i=0;i<N;i++){
			sem_wait(&sN);
		}
	}
	else{
		sem_post(&s);
		sem_wait(&s2);
	}
	sem_post(&s2);

	B();
}

int main(){
	int i;
	sem_init(&s, 0, 1);
	sem_init(&s2, 0, 0);
	sem_init(&sN, 0, 0);
	pthread_t t[N];
	
	for(i=0;i<N;i++){
		pthread_create(&t[i], NULL, f, NULL);
	}
	for(i=0;i<N;i++){
		pthread_join(t[i], NULL);
	}
	
	return 0;
}
/*
void *t1(void *a){
	int i=0;
  for(i=0;i<300000;i++){
  	printf("a");fflush(stdout);sleep(1);}
  return NULL;
}
int main() {
int i;
pthread_t thread, thread2;
  pthread_create (&thread, NULL, t1, NULL);
  sleep(3);
  pthread_cancel (thread);
  sleep(3);
  printf("\nPadre\tPID=%d\n", getpid());fflush(stdout);
  sleep(3);
}
*/
/*
int i=0; pthread_t thread, thread2;
void *t1(void *a){
  pthread_detach (pthread_self ());
  printf ("\nthread1\ti=%d\n", ++i);fflush(stdout);
  return NULL;
}
void *t2(void *a){
  sleep(1);
  printf ("\nthread2\ti=%d\tPID=%d\n", ++i, getpid());fflush(stdout);
  return NULL;
}
int main() {
pid_t pid, pid2;
  if((pid=fork())) pthread_create (&thread, NULL, t1, NULL);
  sleep(1);
  if((pid2=fork())) pthread_create (&thread2, NULL, t2, NULL);
  printf("A");fflush(stdout);
  
  sleep(4);
  if(pid==0&&pid2==0){
	  printf("\nFiglio di F1\tPID=%d\n", getpid());fflush(stdout);
	  exit(0);
  }
  else if(pid!=0&&pid2==0){
	  
	  printf("\nFiglio 2 del padre\tPID=%d\n", getpid());fflush(stdout);
	  exit(0);
  }
  else if(pid==0&&pid2!=0){
	  waitpid(pid2, NULL, 0);
	  
	  printf("\nFiglio 1 del padre\tPID=%d\n", getpid());fflush(stdout);
	  exit(0);
  }
  waitpid(pid, NULL, 0);
  printf("\nPadre\tPID=%d\n", getpid());fflush(stdout);
}
*/
