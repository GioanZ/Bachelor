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

int *pA, *pB, *pC, *pD, *pE, *pF, *pG, *pH, *pI;

int *make_sem() {
	int *sem;
	sem = calloc(2,sizeof(int));
	pipe(sem);
	return sem;
}

void sem_pipe_wait(int * s) {
	int junk;
	if (read(s[0], &junk, 1) <=0) {   // it blocks if pipe is empty
		fprintf(stderr, "ERROR : wait\n");
		exit(1);
	}
}

void sem_pipe_post(int * s) {
	if (write(s[1], "x", 1) <=0) {
		fprintf(stderr, "ERROR : signal\n");
		exit(1);
	}
}


void tA(){

	while(1){
		sem_pipe_wait(pA);
		printf("  A\n");fflush(stdout);
		sem_pipe_post(pB);
		sem_pipe_post(pC);
		sem_pipe_post(pD);
	}
}
void tB(){

	while(1){
		sem_pipe_wait(pB); 
		printf("B");fflush(stdout);
		sem_pipe_post(pI);
	}
}
void tC(){
	
	while(1){
		sem_pipe_wait(pC);
		sleep(1);
		printf(" C ");fflush(stdout);
		sem_pipe_post(pE);
		sem_pipe_post(pF);
	}
}
void tD(){

	while(1){
		sem_pipe_wait(pD);
		sleep(2);
		printf("D\n");fflush(stdout);
		sem_pipe_post(pH);
	}
}
void tE(){

	while(1){
		sem_pipe_wait(pE);
		sleep(3);
		printf(" E ");
		fflush(stdout);
		sem_pipe_post(pG);
	}
}
void tF(){

	while(1){
		sem_pipe_wait(pF);
		sleep(4);
		printf("F\n");
		fflush(stdout);
		sem_pipe_post(pG);
	}
}
void tG(){

	while(1){
		sem_pipe_wait(pG);
		sem_pipe_wait(pG);
		sleep(2);
		printf("  G");
		fflush(stdout);
		sem_pipe_post(pI);
	}
}
void tH(){

	while(1){
		sem_pipe_wait(pH);
		sleep(6);
		printf(" H\n");
		fflush(stdout);
		sem_pipe_post(pI);
	}
}
void tI(){

	while(1){
		sem_pipe_wait(pI);
		sem_pipe_wait(pI);
		sem_pipe_wait(pI);
		printf("  I\n");
		fflush(stdout);
		sleep(1);
		sem_pipe_post(pA);
	}
}

int main(int argc, char **argv){// gcc ex2.c -o ex2P -lpthread -lrt
	//	./ex2P
	
	pA=make_sem();
	pB=make_sem();
	pC=make_sem();
	pD=make_sem();
	pE=make_sem();
	pF=make_sem();
	pG=make_sem();
	pH=make_sem();
	pI=make_sem();
	
	sem_pipe_post(pA);
	if(fork()){//padre
		if(fork()){//padre
			if(fork()){//padre
				if(fork()){//padre
					if(fork()){//padre
						if(fork()){//padre
							if(fork()){//padre
								if(fork()){//padre
									tI();
									wait(NULL);
								}
								else{
									tH();
								}
							}
							else{
								tG();
							}
						}
						else{
							tF();
						}
					}
					else{
						tE();
					}
				}
				else{
					tD();
				}
			}
			else{
				tC();
			}
		}
		else{
			tB();
		}
	}
	else{
		tA();
	}
	
	return 0;
}
/*
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

sem_t sA, sB, sC, sD, sE, sF, sG, sH, sI;

void *tA(void *arg){

	while(1){
		sem_wait(&sA);
		printf("  A\n");
		sem_post(&sB);
		sem_post(&sC);
		sem_post(&sD);
	}
}
void *tB(void *arg){

	while(1){
		sem_wait(&sB); 
		printf("B");
		sem_post(&sI);
	}
}
void *tC(void *arg){

	while(1){
		sem_wait(&sC);
		sleep(1);
		printf(" C ");
		sem_post(&sE);
		sem_post(&sF);
	}
}
void *tD(void *arg){

	while(1){
		sem_wait(&sD);
		sleep(2);
		printf("D\n");
		sem_post(&sH);
	}
}
void *tE(void *arg){

	while(1){
		sem_wait(&sE);
		sleep(3);
		printf(" E ");
		sem_post(&sG);
	}
}
void *tF(void *arg){

	while(1){
		sem_wait(&sF);
		sleep(4);
		printf("F\n");
		sem_post(&sG);
	}
}
void *tG(void *arg){

	while(1){
		sem_wait(&sG);
		printf("  G");
		sem_post(&sI);
	}
}
void *tH(void *arg){

	while(1){
		sem_wait(&sH);
		sleep(6);
		printf(" H\n");
		sem_post(&sI);
	}
}
void *tI(void *arg){

	while(1){
		sem_wait(&sI); 
		sem_wait(&sI); 
		sem_wait(&sI);
		printf("  I\n");
		sem_post(&sA);
	}
}

int main(int argc, char **argv){
	int i=0;
	pthread_t t[9];
	
	sem_init(&sA, 0, 1);
	sem_init(&sB, 0, 0);
	sem_init(&sC, 0, 0);
	sem_init(&sD, 0, 0);
	sem_init(&sE, 1, 0);
	sem_init(&sF, 1, 0);
	sem_init(&sG, 0, 0);
	sem_init(&sH, 1, 0);
	sem_init(&sI, 1, 0);
	
	if(fork()){//padre
		if(pthread_create(&t[0],NULL,&tA,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[1],NULL,&tB,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[2],NULL,&tC,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[3],NULL,&tD,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[8],NULL,tI,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
	}
	else{
		if(pthread_create(&t[4],NULL,&tE,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[5],NULL,&tF,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[6],NULL,&tG,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		if(pthread_create(&t[7],NULL,&tH,NULL)){
			printf("Errore nel thread\n");
		}else printf("aperto\n");
		
		for(i=3;i<8;i++){
			pthread_join(t[i], NULL);
		}
		
		exit(0);
	}

	for(i=0;i<3;i++){
			pthread_join(t[i], NULL);
	}
	pthread_join(t[8], NULL);
	printf("Sto per chiudere\n");
	sem_destroy(&sA);
	sem_destroy(&sB);
	sem_destroy(&sC);
	sem_destroy(&sD);
	sem_destroy(&sE);
	sem_destroy(&sF);
	sem_destroy(&sG);
	sem_destroy(&sH);
	sem_destroy(&sI);
	
	return 0;
}


*/


