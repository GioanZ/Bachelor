#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
        int i;
	pid_t pid=0;
	printf("\n\nsono il Padre P con PID: %d\n", getpid());
	
	for(i=0;i<3&&pid==0;i++){
		pid=fork();
		
		if(!pid){
			printf("F: ho il PID: %d\n", getpid());
			printf("\t e mio padre ha il PID: %d\n", getppid());
		}
		else
			wait(NULL);
	}
	if(!pid){
		exit(0);
	}
	printf("\n\n\n");
	return 0;
}
