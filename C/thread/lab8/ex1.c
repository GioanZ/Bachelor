#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

typedef struct {
	char *in, *out;
	int n;
}nomeFile;

void *threadP(void *nFile);
void sort(int *v, int N);

int main(int argc, char **argv){// gcc ex1.c -o ex1P -lpthread
	//./ex1P in1.txt out1.txt in2.txt out2.txt in3.txt out3.txt in4.txt out4.txt
	printf("\n");
	char **nomiFile;
	nomeFile *nFile;
	pthread_t *tid;
	int NF, i, j;
	
	if(((argc-1)%2)!=0||argc<=1){
		printf("Devi mettere in e out file, almeno 1 di ognuno\n");
		exit(-1);
	}
	
	NF=argc-1;
	printf("Crea %d thread:\n", NF/2);
	
	tid = (pthread_t *) malloc(sizeof(pthread_t) * (NF/2));
	nFile = (nomeFile *) malloc(sizeof(nomeFile) * (NF/2));
	nomiFile = (char **) malloc(sizeof(char *) * NF);
	for(i=1, j=0; i <= NF || j < NF / 2;i+=2, j++){
		nFile[j].in = (char *) malloc(sizeof(char) * strlen(argv[i]+1));
		strcpy(nFile[j].in, argv[i]);
		nFile[j].out = (char *) malloc(sizeof(char) * strlen(argv[i+1]+1));
		strcpy(nFile[j].out, argv[i+1]);
		nFile[j].n=j;
		//printf("nome file: %s\t%s\n", nFile[j].in, nFile[j].out);
		pthread_create(&tid[j], NULL, &threadP, (void *) &nFile[j]);
	}
	
	for(i=0;i<NF/2;i++){
		 pthread_join(tid[i], NULL);
	}
	
	
	return 0;	
}

void *threadP(void *arg){
	nomeFile *nF = (nomeFile *) arg;
	FILE *fin=fopen(nF->in, "r");
	FILE *fout=fopen(nF->out, "w");
	int N, *vett, i;
	
	printf("\tThread%d ordina %s e salva il risultato in %s\n", nF->n,nF->in, nF->out);
	
	if(fout==NULL || fin == NULL){
		printf("problemi apertura file\n");
	}
	
	fscanf(fin, "%d", &N);
	vett=(int *)malloc(N*sizeof(int));
	for(i=0;i<N;i++){
		fscanf(fin, "%d", &vett[i]);
	}
	
	sort(vett, N);
	
	for(i=0;i<N;i++){
		fprintf(fout, "%d\n", vett[i]);
	}
	
	fclose(fin);
	fclose(fout);
	pthread_exit(NULL);
}

void sort(int *v, int N){
	int i, j, tmp;
	printf("sort\n"); 
	for(i=0;i<N;i++){
		for(j=0;j<i;j++){
			if(v[i]<v[j]){
				tmp=v[i]; //swap 
				v[i]=v[j];
				v[j]=tmp;
			}

		}
	} 
}
