#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define N 50

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
	
	return 0;
}
