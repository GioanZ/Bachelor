#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void manager (int sig) {
printf ("Ricevuto il segnale %d\n", sig);
// (void) signal (SIGINT, manager);
return;
}
int main() {
(void) signal (SIGINT, manager);
while (1) {
printf ("main: Hello!\n");
sleep (1); 
}
}
