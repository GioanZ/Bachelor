#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define N 4
#define m 3
#define n 11
/*
Si descriva, in linguaggio C, un codice in grado di chiamare N threads in grado di effettuare la somma per righe di una matrice m x n. 
Si riporti il codice C della funzione main, del codice con system call per la chiamata dei threads e della funzione thread chiamata.
*/
int mat[m][n]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,5,7,4,4,7,7,4,5,7,1,6};

typedef struct{
	int a, b, liv, res;
}Interv;

void *thread(void *arg){
	Interv *st = (Interv *) arg;
	int res=0, i;
	for(i=st->a;i< st->b;i++){
		res+=mat[st->liv][i];
	}
	st->res=res;
	
	pthread_exit((void *) res);
}

int main(int argc, char **argv){	//	gcc exS9_7.c -o exS9_7 -lpthread
					//	./exS9_7
	int i, j, k, res, div, resto, a, b, res2;
	pthread_t tid[N];
	void *status;
	//Interv *tp=(Interv *) malloc(sizeof(Interv)*N);
	Interv tp[N];
	a=0;
	b=n;
	div=(b-a)/N;
	for(i=0;i<m;i++){
		a=0;
    		resto=(b-a)%N;
		for(k=0;k<N;k++){
			tp[k].a=a;
			tp[k].b=div + a;
			if(resto>0){
				tp[k].b++;
				resto--;
			}
			a = tp[k].b;
			if (k==N-1) {
				tp[k].b = b;
			}
			tp[k].liv=i;
			printf("intervallo messo: a=%d\tb=%d\tliv=%d\n", tp[k].a, tp[k].b, tp[k].liv);
			pthread_create(&(tid[k]), NULL, thread, (void *) &tp[k]);
		}
		for(j=0;j<n;j++){
			printf("%d ", mat[i][j]);
		}
		for(k=0, res=0,  res2=0;k<N;k++){
			pthread_join(tid[k], &status);
			res+=(int) status;
			res2+=tp[k].res;
		}
		printf("\t%d\t%d", res, res2);
		printf("\n");
	}
	
	return 0;
}
