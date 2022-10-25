#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////FORK()
//#include <sys/types.h>
#include <unistd.h>	////////SLEEP() EXEC()
////////FORK()

////////WAIT()
#include <sys/wait.h>

void stamp(char c){
	for(int i=0;i<10;i++)
		printf("%c", c);
}
int main(int argc, char **argv){
	
	pid_t pid[N];
	int i;
	char c='a';
	
	for(i=0;i<N;i++){
		if(((int)c)>((int)'z'))
			c='a';
		if(fork()==0){
			stamp(c);
			exit(0);
		}
		c+=1;
		wait(NULL);
	}
	printf("\n");
	return 0;
}

