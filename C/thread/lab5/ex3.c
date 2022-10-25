#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUF_SIZE 53

void leggiSonX(char *s){

	char* dstFile="./proviamo.txt";
	char buf[BUF_SIZE];
        int inputFd, i;
	ssize_t numRead;
	

	inputFd=open(s, O_RDONLY);
	
	if(inputFd==-1){
		printf("Errore input file\n");
		return;
	}
	else{
		printf("file sorgente: %s\n", s);
	}
	
	//read restituisce il numero di byte letti, 0 se ha finito, -1 se ci sono stati errori
	numRead=read(inputFd, buf, BUF_SIZE);
	printf("byte letti:\t%d\n", numRead);
	for(i=0;i<50;i++){
		printf("%c\n", buf[i]);
	}
        close(inputFd);
}

void nonCapisco(){
	printf("AAAOOOO\n");
	return;
}

int main(int narg, char *argv[]){
	
	signal(SIGCHLD, nonCapisco);
	
	pid_t pid[2]={0};
	int status;
	
	pid[0]=fork();
	
	if(pid[0]!=0){
		pid[1]=fork();/*
		if(pid[1]==0)
			pid[0]=0;*/
	}
	
	if(pid[0]!=0&&pid[1]!=0){//padre
		printf("Sono il padre con PID=%d\nHo creato due figli:\n\tfiglio1:\t%d\n\tfiglio2:\t%d\n", getpid(), pid[0], pid[1]);
		waitpid(pid[1], &status, 0);
		printf("fatto EXIT1\n");
		if(WIFEXITED(status)){
			printf("il figlio con PID=%d è terminato con exit(%d)\n", pid[1], WEXITSTATUS(status));
		}
		else{
			printf("il figlio non è terminato correttamente\n");
		}
		waitpid(pid[0], &status, 0);
		printf("fatto EXIT0\n");
		if(WIFEXITED(status)){
			printf("il figlio con PID=%d è terminato con exit(%d)\n", pid[0], WEXITSTATUS(status));
		}
		else{
			printf("il figlio non è terminato correttamente\n");
		}
	}
	else if(pid[0]!=0){//figlio 2
		printf("Sono il figlio2 con PID=%d\n", getpid());
		leggiSonX("son2.txt");
		sleep(5);
		printf("faccio EXIT2\n");
		exit(2);
	}
	else{//figlio 1
		printf("Sono il figlio1 con PID=%d\n", getpid());
		leggiSonX("son1.txt");
		printf("faccio EXIT1\n");
		exit(1);
	}
	
	
			
	return 0;
}
