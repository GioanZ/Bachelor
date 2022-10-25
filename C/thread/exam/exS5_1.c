#include <stdio.h>
#include <stdlib.h>

////////FORK()
//#include <sys/types.h>
#include <unistd.h>	////////SLEEP()
////////FORK()

////////WAIT()
#include <sys/wait.h>
////////WAIT()

#define N 100

/*
Scrivere un programma C in cui il processo padre procede alla generazione di un numero N di figli.
Ciascun figlio è incaricato di stampare a terminale 10 volte una lettera dell’alfabeto, ottenuta scostandosi dalla lettera ‘a’ un numero
										di lettere pari all’ordine di generazione del figlio stesso.
Si richiede un output ordinato: prima dovranno essere stampate le 10 ‘a’, quindi le 10 ‘b', ...
*/

//	gcc  exS5_1.c -o exS5_1
//	./exS5_1

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
