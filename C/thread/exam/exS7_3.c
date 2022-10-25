#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
/*
Si scriva un programma in C in cui un processo padre P, crea due figli A e B,
		ciascuno dei quali invia al processo padre un numero (utilizzando una pipe opportunamente istanziata).
		Successivamente il padre invia a ciascun figlio (utilizzando due ulteriori pipe) un numero casuale 
											compreso tra 1 e il numero precedentemente ricevuto.
*/
int main(int argc, char **argv){
	pid_t pidA, pidB;
	int pipeA1[2], pipeB1[2], pipeA2[2], pipeB2[2], n=0, a=0, b=0;
	pipe(pipeA1);
	pipe(pipeA2);
	pipe(pipeB1);
	pipe(pipeB2);
	
	pidA=fork();
	if(pidA==0){	//	A
		n=100;
		close(pipeA1[0]);
		write(pipeA1[1], &n, sizeof(int));
		close(pipeA1[1]);
		close(pipeA2[1]);
		printf("leggo A\n");
		if (read(pipeA2[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
		}
		close(pipeA2[0]);
		printf("Ricevuto in A %d\n", n);fflush(stdout);
		sleep(1);
		exit(0);
	}
	
	pidB=fork();
	if(pidB==0){	//	B
		n=200;
		close(pipeB1[0]);
		write(pipeB1[1], &n, sizeof(int));
		close(pipeB1[1]);
		close(pipeB2[1]);
		printf("leggo B\n");
		if (read(pipeB2[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
		}
		close(pipeB2[0]);
		printf("Ricevuto in B %d\n", n);fflush(stdout);
		sleep(1);
		exit(0);
	}
	
	close(pipeA1[1]);
	if (read(pipeA1[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
	}
	close(pipeA1[0]);
	printf("Ricevuto da A per P %d\n", n);fflush(stdout);
	n=rand()%n+1;
	printf("Inviato da P per A %d\n", n);fflush(stdout);
	close(pipeA2[0]);
	write(pipeA2[1], &n, sizeof(int));
	close(pipeA2[1]);
	printf("Invio da P per A %d\n", n);fflush(stdout);
	close(pipeB1[1]);
	if (read(pipeB1[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
	}
	close(pipeB1[0]);
	printf("Ricevuto da B per P %d\n", n);fflush(stdout);
	n=rand()%n+1;
	printf("Invio da P per B %d\n", n);fflush(stdout);
	close(pipeB2[0]);
	write(pipeB2[1], &n, sizeof(int));
	close(pipeB2[1]);
	printf("Inviato da P per B %d\n", n);fflush(stdout);
	
	sleep(3);
	return 0;
	
}
/*
int main(int argc, char **argv){
	pid_t pidA, pidB;
	int pipeA[2], pipeB[2], n=0, a=0, b=0;
	pipe(pipeA);
	pipe(pipeB);
	pidA=fork();
	if(pidA==0){	//	A
		n=100;
		write(pipeA[1], &n, sizeof(int));
		//sleep(2);
		if (read(pipeA[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
		}
		close(pipeA[1]);
		close(pipeA[0]);
		printf("Ricevuto in A %d\n", n);fflush(stdout);
		sleep(1);
		exit(0);
	}
	pidB=fork();
	if(pidB==0){	//	B
		n=200;
		write(pipeB[1], &n, sizeof(int));
		//sleep(1);
		if (read(pipeB[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
		}
		close(pipeB[1]);
		close(pipeB[0]);
		printf("Ricevuto in B %d\n", n);fflush(stdout);
		sleep(1);
		exit(0);
	}
	
	if (read(pipeA[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
	}
	printf("Ricevuto da A per P %d\n", n);fflush(stdout);
	n=rand()%n+1;
	printf("Inviato da P per A %d\n", n);fflush(stdout);
	write(pipeA[1], &n, sizeof(int));
	printf("Invio da P per A %d\n", n);fflush(stdout);
	if (read(pipeB[0], &n, sizeof(int)) <= 0) {	// se la pipe è vuota è fermo qua ad aspettare
			fprintf(stderr, "ERROR\n");
			exit(-1);
	}
	printf("Ricevuto da B per P %d\n", n);fflush(stdout);
	n=rand()%n+1;
	printf("Invio da P per B %d\n", n);fflush(stdout);
	write(pipeB[1], &n, sizeof(int));
	printf("Inviato da P per B %d\n", n);fflush(stdout);
	sleep(3);
	return 0;
	
}*/
