#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv){
	pid_t pid=atoi(argv[1]);
	char* s=argv[2];
		
	if(strcmp(s,"fine")==0){
		printf("\nvado in %d\n",pid);
		kill(pid, SIGINT);
	}else{
		if(strcmp(s,"somma")==0){
			printf("\nvado in %d\n",pid);
			kill(pid, SIGUSR2);
		}
		else if(strcmp(s,"differenza")==0){
			printf("\nvado in %d\n",pid);
			kill(pid, SIGUSR1);
		}
		else
			printf("sbagliato segnale\n");
	}
}
