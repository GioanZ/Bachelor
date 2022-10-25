#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	int in, out;
}Struttura;

void *funz(void *arg){
	Struttura *st = (Struttura *) arg;
	Struttura *st2 = (Struttura *) malloc(sizeof(Struttura));
	
	st2->in=29;
	st2->out=st->out=st->in*101;
	sleep(1);
	printf("\ndentro t\tst2->in=%d\tt2->out=%d\n\n",st2->in, st2->out);
	pthread_exit((void *)st2);
}

int main(int argc, char **argv){// 	gcc exS9_9.c -o exS9_9 -lpthread
				//	./exS9_9
	
	Struttura strutIn;
	Struttura *strutOut= (Struttura *) malloc(sizeof(Struttura));
	pthread_t tid;
	
	strutIn.in=4;
	strutIn.out=-1;
	strutOut->in=-1;
	strutOut->out=-1;
	printf("prima create\nstrutIn.in=%d\tstrutIn.out=%d\tstrutOut.in=%d\tstrutOut.out=%d\n",strutIn.in, strutIn.out, strutOut->in, strutOut->out);
	if(pthread_create(&tid, NULL, funz, (void *) &strutIn)){
		printf("Error\n");
		exit(-1);
	}
	sleep(1);
	printf("dopo create\nstrutIn.in=%d\tstrutIn.out=%d\tstrutOut.in=%d\tstrutOut.out=%d\n",strutIn.in, strutIn.out, strutOut->in, strutOut->out);
	sleep(2);
	printf("prima join\nstrutIn.in=%d\tstrutIn.out=%d\tstrutOut.in=%d\tstrutOut.out=%d\n",strutIn.in, strutIn.out, strutOut->in, strutOut->out);
	pthread_join(tid, (void **)&strutOut);
	printf("dopo join\nstrutIn.in=%d\tstrutIn.out=%d\tstrutOut.in=%d\tstrutOut.out=%d\n",strutIn.in, strutIn.out, strutOut->in, strutOut->out);
	strutIn.in=-7;
	printf("dopo modifica strutIn.in\nstrutIn.in=%d\tstrutIn.out=%d\tstrutOut.in=%d\tstrutOut.out=%d\n",strutIn.in, strutIn.out,  strutOut->in, strutOut->out);
	
	return 0;	
}
