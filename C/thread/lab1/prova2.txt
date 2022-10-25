#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;

	pid = fork();

	if(pid <0){
		printf("problema\n");
	}
	else if(pid==0){
		execlp("/bin/ls","ls",NULL);
		printf("bella figlio\n");
	}
	else{
		printf("padre\n");
		wait(NULL);
		printf("bellapadre\n");
	}
}
