#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
        int i;
        //EXTRA
        pid_t pid;
        
        printf("\n\nsono il Padre P con PID: %d\n", getpid());
	//
        for(i=2;i>=1;i--){
                if(!(pid=fork())){
                        printf("%d\n",-i);
                }
                else
                	printf("%d\n",i);
                //EXTRA
                if(!pid){
			printf("F: ho il PID: %d\n", getpid());
			printf("\t e mio padre ha il PID: %d\n", getppid());
		}
		else
			wait(NULL);
		//
        }
       
        if(!pid){
		exit(0);
	}
	printf("\n");
	return 0;
}
