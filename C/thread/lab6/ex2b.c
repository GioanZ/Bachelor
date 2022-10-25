#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define SIZE 1000

int main(int argc, char **argv){
	int i=0, j=0;
	char s[SIZE+1];
	
	fgets(s, SIZE, stdin);//N.B. mette in s anche \n
	for(i=0;i<strlen(s);i++){
		/*if(s[i]=='\n'){//N.B. alla fine entra in questo if
			printf("va a capo\n");
		}*/
		s[i]=toupper(s[i]);
	}
	
	printf("%s\n", s);
	
	return 0;
}
