#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>
// gcc exS3_4.c -o exS3_4
int main () 
{
    int status=0;
    pid_t pid_f1, pid_f2, pid_n;
    pid_f1 = fork (); // T1 
    if (pid_f1 == 0)
    { 
        pid_n = fork (); 
        if (pid_n == 0) 
        { 
        printf("sono figlioN %d\n", getpid());
         execlp ("echo", "nipote", "ls -a", NULL); // T2 
         exit (-1); 
         } 
         printf("sono figlio 1 %d\n", getpid());
         wait (&status); 
         printf("status1\t%d\n", WEXITSTATUS(status));
         printf("status1_2\t%d\n", status);
      exit (pid_n); 
      } 
    wait (&status);
    printf("status2\t%d\n", WEXITSTATUS(status));
    printf("status2_2\t%d\n", status);
    pid_f2 = fork (); 
    if (pid_f2 == 0) 
    { 
    printf("sono figlio 2 %d\n", getpid());
        execl ("figlio", NULL); // T3
        exit (-1); 
    }
    wait (&status);
    printf("status3\t%d\n", WEXITSTATUS(status));
    printf("status3_2\t%d\n", status);
    printf("sono padre %d\n", getpid());
    return 0;
}
