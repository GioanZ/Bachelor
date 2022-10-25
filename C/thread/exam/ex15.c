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

/*
Si illustrino le caratteristiche dei segnali per inviare informazioni asincrone tra processi.
Si riporti un programma che ne illustri l’utilizzo effettuando le seguenti operazioni:

1. Il programma principale crea due processi figlio, P1 e P2 e rimane in attesa di ricevere segnali da tali processi. 
	Ogni volta che riceve un segnale da P1 visualizza su standard output il messaggio "Segnale ricevuto da P1". 
	Analogamente, ogni volta che riceve un segnale da P2 visualizza su standard output il messaggio "Segnale ricevuto da P2". 
	Se però riceve 3 segnali consecutivi dallo stesso processo, uccide i processi P1 e P2, utilizzando il comando di shell 
															"kill" e termina.
2. I processi P1 e P2 eseguono un ciclo infinito, all'interno del quale attendono un tempo casuale e 
	poi inviano un messaggio al processo padre. P1 trasferisce segnali di tipo SIGUSR1; P2 trasferisce segnali di tipo SIGUSR2. 
*/

int p1=0, p2=0;

void sign_handler(int sig){
	if (sig==SIGUSR1){
		p1++;
		p2=0;
		printf("Segnale ricevuto da P1\n");
	}
	else if (sig==SIGUSR2) {
		p2++;
		p1=0;
		printf("Segnale ricevuto da P2\n");
	}
}



int main(int argc, char **argv){		//	gcc ex15.c -o ex15
	pid_t pid1, pid2;	char cmd[100];	//	./ex15
	if ( (signal(SIGUSR1, sign_handler) == SIG_ERR) || (signal(SIGUSR2, sign_handler ) == SIG_ERR) ) {
		printf("Errore inizializzazione del signal handler");
		exit(-1);
	}
	
	if((pid1=fork())==0){//P1
		while(1){
			sleep(rand()%2);
			kill(getppid(), SIGUSR1);
		}
		exit(0);
	}
	if((pid2=fork())==0){//P2
		while(1){
			sleep(rand()%3);
			kill(getppid(), SIGUSR2);
		}
		exit(0);
	}

	/* Padre */
	while (1) {
		pause();sleep(1);
		if (p2==3||p1==3) {
			/* Kill P1 con un comando di shell */
			printf("Kill P1 con un comando di shell");
			sprintf(cmd, "kill -KILL %d", pid1);
			system(cmd);
			/* Kill P2 con un comando di shell */
			printf("Kill P2 con un comando di shell");
			sprintf(cmd, "kill -s SIGKILL %d", pid2);
			system(cmd);
			exit(0);
		}
	}
}
