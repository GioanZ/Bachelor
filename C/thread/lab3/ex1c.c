#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
        int i;
        //EXTRA
        pid_t pid, pid2;
        
        printf("\n\nsono il Padre P con PID: %d\n", getpid());
	//
        for(i=0;i<2;i++){
                if(!(pid=fork())){
                        pid2=fork();
                }
                /*FALLITO TROPPI FORK//EXTRA
                if(!pid||!pid2){
			printf("F: ho il PID: %d\n", getpid());
			printf("\t e mio padre ha il PID: %d\n", getppid());
		}
		else
			wait(NULL);
		//é/
        }
        printf("%d\n",i);
        if(!pid||!pid2){
		exit(0);
	}
	printf("\n");
	return 0;
}
