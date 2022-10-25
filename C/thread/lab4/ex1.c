#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 50

void stampa50NumCasuali(){
	int i, r;
	for(i=0;i<N;i++){
		r=rand()%100;
		printf("%d\t%d\n", r, r*r);		
	}
}

void stampaNumCasuale(){
	printf("%d\n", rand()%100);
	sleep(4);
}

int main(){
	pid_t pid[6]={0};
	int i , j;

	/* va bene se vuoi
	i=-1;
	do{
		i++;
		pid[i]=fork();
	}while(pid[i]!=0&&i<5);*/
	for(i=0;i==0||(i<6&&pid[i-1]!=0);i++){
		pid[i]=fork();
		if(pid[i]==0){
			srand(getpid());
			printf("sono il figlio %d con PPID=%d e con PID=%d\n", i, getppid(), getpid());
			while(1){
				switch(i+1){
				case 1:
					stampaNumCasuale();
					break;
				case 2:
					stampaNumCasuale();
					break;
				case 3:
					stampaNumCasuale();
					break;
				case 4:
					stampa50NumCasuali();
					exit(1);
				case 5:
					stampa50NumCasuali();
					exit(1);
				case 6:
					stampa50NumCasuali();
					exit(1);
				defaul:
					printf("\n\nPROBLEMA\n\n");
				}
			}
		}
	}

	printf("sono il padre con PID=%d\n", getpid());
	for(j=0;j<6;j++){
		printf("\til figlio %d ha PID=%d\n", j+1, pid[j]);
		wait(NULL);
	}
	return 0;
}
