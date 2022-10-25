#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

//	gcc exS6_3.c -o exS6_3
//	./exS6_3

int main(int argc, char **argv){
	int i=1;
	pid_t pid;
	
	if((pid=fork())==0){
		while(1){
			printf("uscito dalla pause\n");
			sleep(1);
		}
		while(1);
		printf("chiudo figlio");
		exit(0);
	}
	sleep(1);
	sleep(3);
	printf("dopo sleep\n");
	kill(pid, SIGUSR1);
	sleep(3);
	printf("dopo sleep\n");
	raise(SIGUSR2);//==kill(getpid(), SIGUSR2);
	while(1);
	
	return 0;
}
