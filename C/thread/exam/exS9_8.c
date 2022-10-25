#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 3

void *funz(void *arg){
	int *res=(int *) malloc(sizeof(int));
	*res= *((int *) arg);

	printf("thread %d\n", *res);
	pthread_exit((void *)*res);
}
int main(int argc, char **argv){
	pthread_t tid[N];
	int status[N]={0}, i;
	void *stat;
	int j;
	for(i=0;i<N;i++){
		j=i+10;
		pthread_create (&(tid[i]), NULL, funz, (void *) &j);
		sleep(1);
	}
	for(i=0;i<N;i++){
		pthread_join (tid[i], &stat);
		status[i]= (int) stat;
	}
	for(i=0;i<N;i++){
		printf ("%d	status=%d\n", i, status[i]);
	}

	return 0;
}

