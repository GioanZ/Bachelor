#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 20

char s[N+1]="";

void *stamp(){//gcc ex2.c -o ex2P -lpthread
	sleep(1);
	
	while(strcmp(s, "exit")!=0){
		if(strcmp(s, "casa")==0||strcmp(s, "house")==0){
			printf("casa rilevata\n");
		}
		sleep(1);
	}
		
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	
	pthread_t tid;
	
	if(pthread_create(&tid, NULL, &stamp, NULL)==0){
		printf("thread creato\n");
	}
	else{
		printf("qualcosa andato storto per la creazione del thread\n");
	}
	
	do{
		printf("Immetti stringa: ");
		scanf("%s", s);
	}while(strcmp(s, "exit")!=0);
	
	pthread_join(tid, NULL);
	
	return 0;	
}




























