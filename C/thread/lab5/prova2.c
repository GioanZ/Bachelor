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
	printf("sottrazione: %d\n", res);
	
	return;
}

void finisci(){
	printf("faccio un ultima sottraz\n");
	kill(getpid(), SIGUSR1);
	printf("ho ripristinato SIGUSR1\n");
	signal (SIGUSR1, SIG_DFL);
	printf("chiudo\n");
	kill(getpid(), SIGUSR1);
	
	return;
}
void figlio(){
	printf("sono dentro figlio %d\n", getpid());
	pause();
	printf("esco dal figlio\n");
}
int main(int argc, char **argv){
	char s[100];
	signal(SIGUSR2, somma);
	signal(SIGUSR1, sott);
	signal(SIGINT, finisci);
	
	printf("Scrivi i numeri a e b\n\t");
	scanf("%d", &a);
	scanf("%d", &b);
	
	if(fork()==0){
		figlio();
		printf("F esegue exit\n");
		exit(0);
	}
	
	while(1){
		printf("\n%d\nComando:\tsegnale\n\"somma\":\tSIGUSR2\n\"differenza\":\tSIGUSR1\n\"fine\":\t\tSIGINT\n\t",getpid());
		printf("Digita in un altro terminale kill -s SEGNALE PID\n"
			"NB senza -s il segnale si comporta di default\n"
			"NB se fai kill -USRX PID || kill -INT PID è come usare -s\n");
		pause();
	}
	
}
