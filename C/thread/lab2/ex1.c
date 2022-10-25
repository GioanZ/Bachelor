#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#define BUF_SIZE 1024

//Da terminale:		./ex1P ../lab1/edit.txt editC.txt

int main(int narg, char *argv[]){

        char srcFile[1000], dstFile[1000], buf[BUF_SIZE];
        int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead, numWrite;

	if(narg!=3){
		printf("Errore numero input\n");
		return 1;
	}

	strcpy(srcFile, argv[1]);
	strcpy(dstFile, argv[2]);
        
	openFlags= O_CREAT | O_WRONLY | O_TRUNC;
	filePerms= 00700 | 00070 | 00007;//S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;//00700 | 00070 | 00007;

	inputFd=open(srcFile, O_RDONLY);
	outputFd=open(dstFile, openFlags/*, S_IRWXU*/, filePerms);
	
	if(inputFd==-1){
		printf("Errore input file\n");
	}
	else{
		printf("file sorgente: %s\n", srcFile);
	}
	if(outputFd==-1){
		printf("Errore output file\n");
	}
	else{
		printf("file destinazione: %s\n", dstFile);
	}
	
	//read restituisce il numero di byte letti, 0 se ha finito, -1 se ci sono stati errori
	numRead=read(inputFd, buf, BUF_SIZE);
	printf("byte letti: %d\n", numRead);
	while(numRead>0){
		//write restituisce il numero di byte scritti, 0 se ha raggiunto la fine del file, -1 se ci sono stati errori
		if((numWrite=write(outputFd, buf, numRead))!=numRead){
			printf("impossibile scrivere l'intero buffer\n");
		}
		printf("byte scritti: %d\n", numWrite);
		if(numRead==-1)
			printf("leggo\n");
		/*
		if(close(inputFd)==-1)
			printf("chiudi input\n");
		if(close(outputFd)==-1)
			printf("chiudi output\n");*/
		numRead=read(inputFd, buf, BUF_SIZE);
		printf("numRead: %d\n", numRead);
        }
        close(inputFd);
        close(outputFd);
        printf("\n\nfine\n");
        return 0;
}
