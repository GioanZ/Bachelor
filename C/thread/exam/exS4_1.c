#include <stdio.h>
#include <stdlib.h>

////////FORK()
#include <sys/types.h>
#include <unistd.h>
////////FORK()


////////WAIT()
#include <sys/wait.h>
////////WAIT()

// gcc exS4_1.c -o exS4_1
/*
Si vuole realizzare un programma in linguaggio C in grado di generare due processi padre/figlio in cui: 
	1) Il processo padre scrive la sequenza di caratteri [A-Z][a-z] in un file di testo (aperto prima di eseguire la fork) e 
											successivamente chiude e rimuove il file creato 
	2) Il processo figlio attende 5 secondi (tramite la funzione “sleep (num_secs)”) e stampa il contenuto del file precedentemente 
											gestito dal processo padre
*/

int main(int argc, char **argv){
	FILE *f=fopen("provaS4_1.txt", "w+");
	pid_t pid;
	int i;
	char c;
	
	pid=fork();
	if(pid==0){//FIGLIO
		sleep(5);
		rewind ( f );
		c = fgetc ( f );
		while ( ! feof ( f ) )
		{
			printf ("%c" , c);
			c = fgetc ( f );
		}
		printf ("\n");
		fclose ( f );
		exit ( 0 );
	}
	else{//PADRE
		for ( i=65 ; i<=90 ; i++ )
		fputc ( i , f );
		for ( i=97 ; i<=122 ; i++ )
		fputc ( i , f );
		
		fclose ( f );
		remove ( "provaS4_1.txt" );
	}
	wait(NULL);

	return 0;
}





