#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
        int i=1;
	pid_t pid;
	printf("\n\nsono il Padre P con PID: %d\n", getpid());
	
	if((pid=fork())){
		i++;
		wait(NULL);
		printf("P: ho generato il figlio con PID: %d\n",pid);
		if((pid=fork())){
			i++;
			wait(NULL);
			printf("P: ho generato il figlio con PID: %d\n",pid);
			if((pid=fork())){
				i++;
				wait(NULL);
				printf("P: ho generato il figlio con PID: %d\n",pid);
			}
		}

	}
	if(pid==0){
		printf("F: sono il %d-esimo\n",i);
		printf("\tcon PID: %d, perché il fork() ha reso: %d\n",getpid(),pid);
		printf("\tcon il padre che ha PID: %d\n",getppid());
		exit(0);
	}
	else{
		printf("\nP: NB io ho PID: %d\npasso e chiudo\n", getpid());
	}

	return 0;
}
