#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define SIZE 1024

int main(int argc, char **argv){
	pid_t pid;
	int pipeFD[2], byteRead;
	FILE *f;
	char s[SIZE];
	
	pipe(pipeFD);
	printf("ho letto %d\n", argc);fflush(stderr);
	
	if((pid=fork())){//P
		close(pipeFD[1]);
		while(1){
			if((byteRead=read(pipeFD[0], s, SIZE))>=0){
				if(strcmp(s, "FINEBELLA\n")==0){
					printf("finito!!!!!!!!!!!!!1\n");fflush(stderr);
					break;
				}
				printf("ho letto %d, ovvero:\n\t%s\n", byteRead, s);fflush(stderr);
			}
		}
		close(pipeFD[0]);
		wait(NULL);
	}
	else{//Child
		close(pipeFD[0]);
		f=fopen("testo.txt", "r");
		if(f==NULL){
			printf("errore apertura file");fflush(stderr);
		}
		while(fgets(s, SIZE, f)){
			write(pipeFD[1], s, strlen(s)+1);
			sleep(1);
		}
		fclose(f);
		close(pipeFD[1]);
		printf("addio figlio\n");fflush(stderr);
		exit(0);
	}
	return 0;	
}
