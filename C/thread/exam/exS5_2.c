#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////FORK()
//#include <sys/types.h>
#include <unistd.h>	////////SLEEP() EXEC()
////////FORK()

////////WAIT()
#include <sys/wait.h>
////////WAIT()

//	gcc  exS5_2.c -o exS5_2
//	./exS5_2

int main(int argc, char **argv){
	char cmd[100];
	int status;
	
	if(argc!=2){
		printf("manca argv[1], metti tipo \"ls\"\nhai messo %d argc e devono essere 2\n\n", argc);
		if (argc==3)
			printf("%s\t%s\t%s", argv[0], argv[1], argv[2]);
		exit(-1);
	}
	strcpy(cmd, argv[1]);
	if(fork()==0){
		execlp(cmd, "nomeInutile", NULL);
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando %s riuscito\n", cmd);
	}
	else{
		printf("problema2\n");
	}
		
	return 0;
}
