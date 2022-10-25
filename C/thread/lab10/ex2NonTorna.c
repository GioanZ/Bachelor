#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

typedef int * Semaphore;

Semaphore semA,semB,semC,semD,semE,semF,semG,semH,semI;

Semaphore make_sem() {
  int *sem;
  sem = calloc(2,sizeof(int));
  pipe(sem);
  return sem;
}

void WAIT(Semaphore s) {
  int junk;
  if (read(s[0], &junk, 1) <=0) {   // it blocks if pipe is empty
    fprintf(stderr, "ERROR : wait\n");
    exit(1);
  }
}

void SIGNAL(Semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}


void pA(){
	while(1) 
	{ 
		WAIT(semA); 
		sleep(1);
		printf("   A\n");
		SIGNAL(semB);        
		SIGNAL(semC);        
		SIGNAL(semD);        
	}
}

void pB(){
        while(1)
	{  
		WAIT(semB);        
		sleep(2);
		printf("B  ");
                fflush(stdout);
		SIGNAL(semI);            
	}
}

void pC(){
	while(1) 
	{  
		WAIT(semC);        
		sleep(3);
		printf("C  ");
                fflush(stdout);
		SIGNAL(semE);        
		SIGNAL(semF);        
	}
}

void pD(){
	while(1) 
	{  
		WAIT(semD);        
		sleep(4);
		printf("D\n");
                fflush(stdout);
		SIGNAL(semH); //in order to implement this graph with minimum number of semaphores the arch D-I has been removed!      
	}
}

void pE(){

        while(1) 
	{
		WAIT(semE);        
		sleep(1);
		printf(" E ");
		fflush(stdout);
		SIGNAL(semG);                
        }

}

void pF(){
	while(1)
  	{  
		WAIT(semF);        
		sleep(2);
		printf("  F\n");
		SIGNAL(semG);        
	}

}


void pG(){
	while(1)
  	{  
		WAIT(semG);        
		WAIT(semG);        
		sleep(1);
		printf("   G");   
		fflush(stdout);
		SIGNAL(semI);        
        }
}

void pH(){  	
	while(1)
  	{
		WAIT(semH);
		sleep(5);
		printf("  H\n");
		SIGNAL(semI);
 	}
}

void pI(){  
  	while(1)
  	{
		WAIT(semI);
		WAIT(semI);
		WAIT(semI); 
		sleep(1);
		printf("   I\n");
		SIGNAL(semA);
  	}

}

int main (int argc, char **argv) {
  int pIDA,pIDB,pIDC,pIDD, pIDE,pIDF,pIDG,pIDH;
                       
  semA=make_sem();
  semB=make_sem();
  semC=make_sem();
  semD=make_sem();
  semE=make_sem();
  semF=make_sem();
  semG=make_sem();
  semH=make_sem();
  semI=make_sem();
  SIGNAL(semA);


    pIDA=fork();
    if (pIDA!=0) {
       pIDB=fork();
       if (pIDB!=0) {
         pIDC=fork(); 
         if (pIDC!=0) {
              pIDD=fork();
              if (pIDD!=0) {
                  pIDH=fork();
                  if (pIDH!=0) {
                      pI();
                    } else
                      pH();    
               } else
                pD();   
           }else {
                pIDE=fork();
                if (pIDE!=0)
                   pC();
                else {
                      pIDF=fork();
                      if (pIDF!=0) {
                         pE();  
                       } else {
                            pIDG=fork();
                            if (pIDG!=0)  
                                pF();
                            else pG(); 
                          }     
                   }   
            }   
          }else
            pB();                        
    }else pA();


       

  // Try to re-implement the processes creation in order to have just one parent creating all processes -> hint: you should implement  a two level tree (1 root n children)    
                              
  return (0);
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
printf(" cjoao A\n");
	while(1){
		sem_wait(&sA);
		printf("  A\n");
		sem_post(&sB);
		sem_post(&sC);
	}
}
void *tB(void *arg){
	while(1){
		sem_wait(&sB); 
		printf("B");
		//sem_post(&sI);
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
		sem_wait(&sG);
		sleep(1); 
		printf("  G");
		sem_post(&sH);
		sem_post(&sI);
	}
}
void *tH(void *arg){
	while(1){
		sem_wait(&sH);
		sem_wait(&sH);
		printf(" H\n");
		sem_post(&sI);
	}
}
void *tI(void *arg){
	while(1){
		sem_wait(&sI); 
		sem_wait(&sI); 
		sem_wait(&sI); 
		sleep(1); 
		printf("  I\n");
		sem_post(&sA);
	}
}

int main(int argc, char **argv){// gcc ex2.c -o ex2P -lpthread -lrt
	//	./ex2P
	int i;
	pthread_t t[9];
	
	sem_init(&sA, 0, 1);
	sem_init(&sB, 0, 0);
	sem_init(&sC, 0, 0);
	sem_init(&sD, 1, 0);
	sem_init(&sE, 0, 0);
	sem_init(&sF, 0, 0);
	sem_init(&sG, 1, 0);
	sem_init(&sH, 1, 0);
	sem_init(&sI, 1, 0);
	
	while(1){
		if(fork()){//padre
			//sem_wait(&sD);
			pthread_create(&t[3], NULL, &tD, NULL);
			if(fork()){//padre
				pthread_create(&t[4], NULL, &tE, NULL);
				pthread_create(&t[5], NULL, &tF, NULL);
				wait(NULL);
				sem_wait(&sI);
				if(!fork()){
					pthread_create(&t[8], NULL, &tI, NULL);
					exit(0);
				}
			}
			else{//figlio
				sem_wait(&sG);
				sem_wait(&sH);
				pthread_create(&t[6], NULL, &tG, NULL);
				pthread_create(&t[7], NULL, &tH, NULL);
				sem_post(&sI);
				exit(0);
			}
		}
		else{//figlio
			//printf("primo figlio\n");
			pthread_create(&t[0], NULL, &tA, NULL);
			pthread_create(&t[1], NULL, &tB, NULL);
			pthread_create(&t[2], NULL, &tC, NULL);
			
			sem_post(&sD);
			exit(0);
		}
		
		for(i=0;i<9;i++){
			pthread_join(t[i], NULL);
		}
	}
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

