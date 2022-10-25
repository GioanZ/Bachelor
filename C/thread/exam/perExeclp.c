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

//	gcc perExeclp.c -o execP
//	./execP

int main(int argc, char **argv){
	char cmd[100];
	int status, i=0;
	
	i++;
	if(fork()==0){
		execl("/bin/ls", "nome Random", "-a", "/home/brad/Desktop/temiExam");
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execl("/bin/ls", "nome Random", "-a", "/home/brad/Desktop");
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execl("/bin/echo", "nomeInut","bella broschi", "/home/brad/Desktop");
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	
	i++;
	if(fork()==0){
		execl("/bin/ls", "nomeInut2","-a", NULL);
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execl("/home/brad/Desktop/temiExam/exS5_2.sh", "nome Ranomd", "./exS5_1", NULL);
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execlp("../lab6/ex2ap", "nomeInutile", "argv_1, e come argv[2] ottengo:");// poi come argv[2] mette: " H=" non so perché
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execlp("../lab6/ex2ap", "nomeInutile", "argv_1", "_invece se metto un altro arg non serve il NULL, se no devo mettere NULL");
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	
	i++;
	if(fork()==0){
		execlp("./exS5_2", "bubusette", "ls", NULL);//fa partire exS5_2 [NB deve esserci ./], ma argv[0]="bubusette", argv[1]="ls", se NON metto NULL argv[2]="H="
		exit(-1);
	}
		
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status)==0/*8 bit inferiori, quindi la X di exit(X)*/){
		printf("comando riuscito %d\n\n", i);
	}
	else{
		printf("\nproblema %d\n\n", i);
	}
	
	sleep(20);
	system("echo $(clear)");
	system("ls -a");
	sleep(3);
	system("clear");
	return 0;
}
