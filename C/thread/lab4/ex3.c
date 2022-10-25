#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char str[100];
	int i;
	pid_t pid=0;
	if(!fork()){
		pid=getpid();
		printf("creato BIGfiglio con PID=%d\n", getpid());
	}
	for(i=0;i<2;i++){
		if(fork()!=0){
			sprintf(str, "echo system with i=%d", i);
			system(str);
			wait(NULL);
		}
		else{
			printf("creato figlio con PID=%d\n", getpid());
			sprintf(str, "exec with i=%d", i);
			execlp("echo", "myPgrm", str, NULL);
		}
	}
	if(getpid()==pid){
		printf("sono figlio con PID=%d che mi chiudo\n", getpid());
		exit(0);
	}
	return 0;
}
