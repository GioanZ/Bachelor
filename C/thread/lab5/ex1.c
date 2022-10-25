#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int a=0, b=0;
//manda in esecuzio ./ex1P in un terminale e poi nell'altro kill -s SIGUSRX #PID 
void somma(){
	int res=a+b;
	printf("somma: %d\n", res);
	
	return;
}

void sott(){
	int res=a-b;
	printf("sottrazione: %d\n", res);
	
	return;
}

int main(int argc, char **argv){
	signal(SIGUSR2, somma);
	signal(SIGUSR1, sott);
	
	printf("\n%d\nInserisci numero a e numero b:\n\t",getpid());
	scanf("%d %d", &a, &b);
	
	while(1){
		pause();
	}
	
}
