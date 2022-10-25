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
    printf("  A\n");fflush(stdout);
    sem_post(&sB);
    sem_post(&sC);
    sem_post(&sD);
  }
}
void *tB(void *arg){

  while(1){
    sem_wait(&sB); 
    printf("B");fflush(stdout);
    sem_post(&sI);
  }
}
void *tC(void *arg){

  while(1){
    sem_wait(&sC);
    sleep(1);
    printf(" C ");fflush(stdout);
    sem_post(&sE);
    sem_post(&sF);
  }
}
void *tD(void *arg){

  while(1){
    sem_wait(&sD);
    sleep(2);
    printf("D\n");fflush(stdout);
    sem_post(&sH);
  }
}
void *tE(void *arg){

  while(1){
    sem_wait(&sE);
    sleep(3);
    printf(" E ");fflush(stdout);
    sem_post(&sG);
  }
}
void *tF(void *arg){

  while(1){
    sem_wait(&sF);
    sleep(4);
    printf("F\n");fflush(stdout);
    sem_post(&sG);
  }
}
void *tG(void *arg){

  while(1){
    sem_wait(&sG);
    printf("  G");fflush(stdout);
    sem_post(&sI);
  }
}
void *tH(void *arg){

  while(1){
    sem_wait(&sH);
    sleep(6);
    printf(" H\n");fflush(stdout);
    sem_post(&sI);
  }
}
void *tI(void *arg){

  while(1){
    sem_wait(&sI); 
    sem_wait(&sI); 
    sem_wait(&sI);
    printf("  I\n");fflush(stdout);
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
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[1],NULL,&tB,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[2],NULL,&tC,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
   if(pthread_create(&t[3],NULL,&tD,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[8],NULL,tI,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
  }
  else{
    if(pthread_create(&t[4],NULL,&tE,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[5],NULL,&tF,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[6],NULL,&tG,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    if(pthread_create(&t[7],NULL,&tH,NULL)){
      printf("Errore nel thread\n");fflush(stdout);
    }else printf("aperto\n");fflush(stdout);
    
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
  fflush(stdout);
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
