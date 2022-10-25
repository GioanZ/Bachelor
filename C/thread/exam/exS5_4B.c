#include <stdio.h>
#include <stdlib.h>

//	gcc exS5_4B.c -o exS5_4B
//	./exS5_4B 11

int main(int argc, char **argv){
	int numero = 0, num;
	int fattoriale = 1;
	
	if(argc!=2){
		printf("Non hai messo nomeExe numeroPerFattoriale\n");
		exit(-1);
	}
	numero=atoi(argv[1]);

	if (numero <= 0) {
		printf("numero messo <=0, quindi ti metto 10 perché mi piace a me\n");
		numero=10;
	}
	num=numero;
	while (numero > 0){
		fattoriale *= numero; 
		numero--;
	}
	printf("Il fattoriale di %d vale: %d\n", num, fattoriale);
	
	return 0;
}
