#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

typedef int * Semaphore;

Semaphore semA,semB,semC,semD,semE,semF,semG,semH,semI;

Semaphore make_sem() {
  int *sem;
  sem = calloc(2,sizeof(int));
  pipe(sem);
  return sem;
}

void WAIT(Semaphore s) {
  int junk;
  if (read(s[0], &junk, 1) <=0) {   // it blocks if pipe is empty
    fprintf(stderr, "ERROR : wait\n");
    exit(1);
  }
}

void SIGNAL(Semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}


void pA(){
	while(1) 
	{ 
		WAIT(semA); 
		sleep(1);
		printf("   A\n");
		SIGNAL(semB);        
		SIGNAL(semC);        
		SIGNAL(semD);        
	}
}

void pB(){
        while(1)
	{  
		WAIT(semB);        
		sleep(2);
		printf("B  ");
                fflush(stdout);
		SIGNAL(semI);            
	}
}

void pC(){
	while(1) 
	{  
		WAIT(semC);        
		sleep(3);
		printf("C  ");
                fflush(stdout);
		SIGNAL(semE);        
		SIGNAL(semF);        
	}
}

void pD(){
	while(1) 
	{  
		WAIT(semD);        
		sleep(4);
		printf("D\n");
                fflush(stdout);
		SIGNAL(semH);       
	}
}

void pE(){

        while(1) 
	{
		WAIT(semE);        
		sleep(1);
		printf(" E ");
		fflush(stdout);
		SIGNAL(semG);                
        }

}

void pF(){
	while(1)
  	{  
		WAIT(semF);        
		sleep(2);
		printf("  F\n");
		SIGNAL(semG);        
	}

}


void pG(){
	while(1)
  	{  
		WAIT(semG);        
		WAIT(semG);        
		sleep(1);
		printf("   G");   
		fflush(stdout);
		SIGNAL(semI);        
        }
}

void pH(){  	
	while(1)
  	{
		WAIT(semH);
		sleep(5);
		printf("  H\n");
		SIGNAL(semI);
 	}
}

void pI(){  
  	while(1)
  	{
		WAIT(semI);
		WAIT(semI);
		WAIT(semI); 
		sleep(1);
		printf("   I\n");
		SIGNAL(semA);
  	}

}

int main (int argc, char **argv) {
  int pIDA,pIDB,pIDC,pIDD, pIDE,pIDF,pIDG,pIDH;
                       
  semA=make_sem();
  semB=make_sem();
  semC=make_sem();
  semD=make_sem();
  semE=make_sem();
  semF=make_sem();
  semG=make_sem();
  semH=make_sem();
  semI=make_sem();
  SIGNAL(semA);


    pIDA=fork();
    if (pIDA!=0) {
       pIDB=fork();
       if (pIDB!=0) {
         pIDC=fork(); 
         if (pIDC!=0) {
              pIDD=fork();
              if (pIDD!=0) {
                  pIDH=fork();
                  if (pIDH!=0) {
                      pI();
                    } else
                      pH();    
               } else
                pD();   
           }else {
                pIDE=fork();
                if (pIDE!=0)
                   pC();
                else {
                      pIDF=fork();
                      if (pIDF!=0) {
                         pE();  
                       } else {
                            pIDG=fork();
                            if (pIDG!=0)  
                                pF();
                            else pG(); 
                          }     
                   }   
            }   
          }else
            pB();                        
    }else pA();


                              
  return (0);
}

