#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void manager(int sig){
	printf("Ricevuto segnale %d\n", sig);
	return;
}

//chiama il programma con ./nomeProgramma & 
int main(){
	signal(SIGINT, manager);
	//per azzionarlo usa => kill -SIGINT #processo
	while(1){
		printf("hello\n");
		sleep(1);
		
	}
}
