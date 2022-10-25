#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
        FILE *f, *f2, *f3;
        char s[100];
        int res;
        
        f=fopen("edit.txt","r");
        f3=fopen("prova3.txt","w");
        f2=fopen("prova2.txt","w");
        if(f==NULL){
        	printf("errore file\n");
        	exit(1);
        }
        fprintf(f3, "ciao");
        res=fscanf(f,"%c", &s[0]);
        while(res!=EOF){
                fprintf(f2, "%c",s[0]);
                res=fscanf(f, "%c", &s[0]);
        }
        printf("Hello\n");
        return 0;
}
