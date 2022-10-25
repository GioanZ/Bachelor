#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv){
	int i=2;
	char s[1000];
	
	if(argc<2){
		printf("devi inserire almeno una stringa\n");
		exit(-1);
	}
	
	strcpy(s, argv[1]); 
	printf("sono solo argv[1]=%s\n", s);
	while(argc-i>0){
		strcat (s, " ");
		strcat (s, argv[i]); 
		i++;
	}
	
	//printf("printf: %s\n%d\n", s, argc);
	execlp("echo", "nomeInutile_lab6_ex2A", s, NULL);

	printf("sta parte non viene eseguita ricorda!!!\n");	
}






