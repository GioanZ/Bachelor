#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int a=0, b=0;

void somma(){
	int res=a+b;
	printf("somma: %d\n", res);
	
	return;
}

void sott(int sig){
	int res=a-b;
	/*
	if(sig!=SIGUSR1){
		printf("Errore comando!!!\n");
	}
	else*/
		printf("sottrazione: %d\n", res);
	
	return;
}

void finisci(){
	printf("chiudo\n");
	
	return;
}

int main(int argc, char **argv){
	char s[100];
	signal(SIGUSR2, somma);
	signal(SIGUSR1, sott);
	signal(SIGINT, finisci);
	
	while(1){
		printf("\n%d\nComando:\tsegnale\n\"somma\":\tSIGUSR2\n\"differenza\":\tSIGUSR1\n\"fine\":\t\tSIGINT\n\t",getpid());
		scanf("%s", s);
		
		if(strcmp(s,"SIGINT")==0){
			kill(getpid(), SIGINT);
			
			return 0;
		}else{
			printf("\nInserisci numero a e numero b:\n\t");
			scanf("%d %d", &a, &b);
			if(strcmp(s,"SIGUSR2")==0){
				kill(getpid(), SIGUSR2);
			}
			else if(strcmp(s,"SIGUSR1")==0){
				kill(getpid(), SIGUSR1);
			}
			else
				printf("sbagliato segnale\n");
		}
	}
	
}
