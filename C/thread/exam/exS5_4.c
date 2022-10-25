#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//	gcc exS5_4.c -o exS5_4
//	./exS5_4

int main(int argc, char **argv){
	int i=1;
	
	while(argc>i){
		if(fork()==0){
			execlp("./exS5_4B", "calcFatt", argv[i], NULL);
			printf("Errore\n");
			exit(-1);
		}
		wait(NULL);
		i++;
	}
	
	return 0;
}
