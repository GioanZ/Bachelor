#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10
#define SIZE2 100

double calcola(int i){//compilalo così: gcc ex3.c -lm -o ex3P
	double res = 1.0;
	
	res = exp (i) / i;
	printf("Mando il numero  %lf\n", res);
	
	return res;
}

int main(int argc, char **argv){
	int N, i;
	int pip[2];
	char s[SIZE2];
	double sum = 0; 
	double ret; 
	
	if(argc!=2){
		printf("devi mettere un numero\n./ex3P 4\n");
		exit(-1);
	}
	
	if (pipe(pip) < 0) {
		perror("Error opening the pipe!");
		exit (-1);
	}
	
	if(atoi(argv[1])>SIZE){
		N=SIZE;
	}
	else{
		N=atoi(argv[1]);
	}
	printf("bella N=%d\n", N);
	
	for(i=0;i<N;i++){
		if(fork()){//PADRE
			//N.B. &varibile == indirizzo cella di variabile
			//N.B. *varibile == numero dentro la cella varibile
			//http://www.diag.uniroma1.it//~liberato/struct/mempunt/index.shtml
			read(pip[0], &ret, sizeof(double));
			printf("Ho letto il numero  %lf\n", ret); 
			sum += ret;
			wait(NULL);
		}
		else{//FIGLIO
			close(pip[0]);
			ret = calcola(i+1);
			write(pip[1], &ret, sizeof(double));
			close(pip[1]);
			exit(0);
		}
	}
	close(pip[1]);
	close(pip[0]);
	
	printf("Sum: %lf\n", sum);
	
	return 0;	
}
