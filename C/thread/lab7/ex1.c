#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_t tid[2];

void *stamp(){//gcc ex1.c -o ex1P -lpthread
	pthread_t id = pthread_self();

	if(pthread_equal(id,tid[0])){
		printf("elaborazione del primo thread\n");
	}
	else{
		printf("elaborazione del secondo thread\n");
	}
	
	sleep(5);
	
	if(pthread_equal(id,tid[0])){
		printf("il primo thread termina\n");
	}
	else{
		printf("il secondo thread termina\n");
	}
	
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	
	if(pthread_create(&tid[0], NULL, &stamp, NULL)==0){
		printf("primo thread creato\n");
	}
	else{
		printf("qualcosa andato storto per primo thread\n");
	}
	sleep(1);
	if(!pthread_create(&(tid[1]), NULL, &stamp, NULL)){
		printf("secondo thread creato\n");
	}
	else{
		printf("qualcosa andato storto per secondo thread\n");
	}
	
	sleep(6);//se no il main chiude prima che vengano eseguiti i threads
	//se metti la join al posto della sleep si risolve ed è meglio
	
	return 0;	
}
