#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
1. programma principale genera 2 pipe e due processi figlio (P1 e P2) e rimane in attesa della loro terminazione.
2. Il processo P1 legge da standard input un valore intero n e lo trasferisce al processo P2 sulla prima pipe.
3. Il processo P2 attende di ricevere tale valore e una volta ricevuto, legge da standard input n stringhe e le
        trasferisce al processo P1 sulla seconda pipe. Al trasferimento di ciascuna stringa
        permette la sua lunghezza, in modo che P1 possa ricostruire le informazioni in maniera corretta.
4. Il processo P1 legge da pipe tutte le stringhe ricevute da P2 e le visualizza su standard output.
5. Le attività di P1 e P2 ricominciano dal punto 2
*/
int main(int argc, char **argv){
    int pipe1[2], pipe2[2], n, i, len;
    char s[100];
    
    pipe(pipe1);pipe(pipe2);
    if (fork()) {//PADRE
        if (!fork()) {//FIGLIO P2
            close(pipe1[1]);
            close(pipe2[0]);
            while(1){
                sleep(2);
                if (read(pipe1[0], &n, sizeof(int)) <= 0) {	// it blocks if pipe is empty
		     fprintf(stderr, "ERROR : wait\n");
		     exit(1);
                }
                for (i = 0; i < n; i++) {
                    scanf("%s", s);
                    len = strlen(s);
                    write(pipe2[1], &len, sizeof(int));
                    write(pipe2[1], s, strlen(s)+1);
                }
            }
            close(pipe1[0]);
            close(pipe2[1]);
            exit(0);
        }
    }
    else {//FIGLIO P1
        close(pipe1[0]);
        close(pipe2[1]);
        while(1) {
            printf("inserichi numero: ");
            scanf("%d", &n);
            write(pipe1[1], &n, sizeof(int));
            for (i = 0; i < n; i++) {
                if (read(pipe2[0], &len, sizeof(int)) <= 0) {	// it blocks if pipe is empty
		     fprintf(stderr, "ERROR : wait\n");
		     exit(1);
                }
                read (pipe2[0], s, (len+1) * sizeof(char));
                printf("%s\n\n", s);
                fflush(stdout);
            }
            sleep(1);
        }
        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    }
    wait(NULL);
    wait(NULL);

    return 0;
}
