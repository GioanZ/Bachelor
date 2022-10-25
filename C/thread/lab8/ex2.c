#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef struct{
	int a, b, N, nT;
}Interv;

int primo=TRUE;

void *cercNumPrim(void *arg);

int main(int argc, char **argv){// gcc ex2.c -o ex2P -lpthread
	//per vedere bene la differenza dato che VBox ha 2 di CPU usa:
	//	./ex2P 1215752191 2
	//	./ex2P 1215752191 1		(ci mette 1 secondo in più)
	
	int N, P, i, j, a, resto, div, b;
	pthread_t *tid;
	Interv *intervallo;
	time_t seconds;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	seconds = time(NULL);
	printf("Orario inizio: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("Secondi dopo il 1 gennaio 1970 = %ld\n", seconds);
	if(argc!=3){
		printf("devi mettere ./ex2P N_numeroPrimo P_#thread\n");
		exit(-1);
	}
	
	N=atoi(argv[1]);
	P=atoi(argv[2]);
	if(N<=1||P<=0){
		printf("devi mettere un numero >= 2\ndevi mettere un numero di thread > 0\n");
		exit(0);
	}
	tid = (pthread_t *) malloc(sizeof(pthread_t) * P);
	intervallo = (Interv *) malloc(sizeof(Interv) * P);
	
	a=2;
	b=N/2;
	resto=(b-a)%P;
	div=(b-a)/P;
	
	for(i=0;i<P;i++){
		intervallo[i].N=N;
		intervallo[i].nT=i;
		intervallo[i].a=a;
		intervallo[i].b=div + a;
		if(resto>0){
			intervallo[i].b++;
			resto--;
		}
		a=intervallo[i].b;
		if (i==P-1) {
			intervallo[i].b=N/2+1;
		}
		//printf("intervallo [%d, %d)\n", intervallo[i].a, intervallo[i].b);
		if(pthread_create(&tid[i], NULL, &cercNumPrim, (void *)&intervallo[i])){
			printf("non sono riuscito a creare thread%d", i);
			exit(-1);
		}
		
	}
	/*
	while(1){
		if(primo==FALSE){
			for(i=0;i<P;i++){
				pthread_cancel(tid[i]);	//TERMINA L'ESECUZIONE DEL THREAD IMMEDIATAMENTE
			}
			break;
		}
		//sleep(1);printf("so qua\n");
	}
	//pthread_join LO PUOI METTERE SOLO SE USI pthread_cancel AL POSTO DI pthread_detach*/
	for(i=0;i<P;i++){
		j = pthread_join (tid[i], NULL);
		if (j) {
			printf("Errore chiusura pthread_join\t%d\n\n", i);
			exit (-1);
		}
	}
	
	seconds = time(NULL);
	t = time(NULL);
	tm = *localtime(&t);
	printf("Secondi dopo il 1 gennaio 1970 = %ld\n", seconds);
	printf("Orario fine: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if(primo == TRUE){
		printf("\n%d è un numero primo\nHo usato %d threads\n", N, P);
	}
	
	return 0;	
}

void *cercNumPrim(void *arg){
	Interv *inter = (Interv *) arg;
	int i;
	
	//printf("entrato in t: %d\n", inter->nT);
	for(i=inter->a;i<inter->b && primo != FALSE; i++){
		//printf("i: %d\n", i);
		if((inter->N%i)==0){
			printf("divisibile per %d\n", i);
			primo = FALSE;
			pthread_exit(NULL);
		}
	}
	//printf("devo chiudere t: %d\n", inter->nT);
	pthread_exit(NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

struct thread_parms {
    int N;
    int left;
    int right;
};


int noprime = 0;

void *runner(void *param) {
    int i;
    struct thread_parms * p = (struct thread_parms *) param;

    for (i=p->left; i<=p->right && noprime==0; i++) {
        if (p->N % i == 0) {
            noprime = 1;
            pthread_exit(0);
        }

    }
    pthread_exit(0);
}



int main (){

    int N, P, left, right, i, step, err;

    printf ("Insert the number to test:");
    scanf ("%d",&N);
    do {
        printf ("Insert the number of threads:");
        scanf ("%d",&P);
        if (P>N-2) {
            printf ("ERROR: There are more threads than numbers to test\n");
        }
    } while (P > N-2);


    pthread_t tid[P];
    struct thread_parms tp [P];
    step = ((N/2)-2)/P;
    left = 2;

    for (i = 0; i < P; i++){
        tp[i].left= left;
        tp[i].right= left + step + 1;
        if (i<P-1) {
            tp[i].right=left+step-1;
        } else {
            tp[i].right=N/2;
        }       
        tp[i].N=N;
        err = pthread_create(&tid[i],NULL, &runner,(void *) &tp[i]);
        if (err!=0) {
            printf ("Unable to create thread [%s]",strerror(err));
            exit(1);
        }
        left += step;   
    }
    for (i=0; i<P; i++) {
        pthread_join (tid[i],NULL);
        if (noprime !=0){
            printf ("%d is not prime \n",N);
            exit (1);
        }
    }
    if (noprime == 0){
            printf ("%d is prime \n",N);
    }
}

*/
