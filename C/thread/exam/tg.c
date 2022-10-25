#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main (int argc, char *argv[]) {
	int i;
	char str[50];
	printf("appena creato PID=%d\n", getpid());
	i = atoi (argv[1]);
	printf ("0 - run with i=%d\n", i); fflush (stdout);
	if (i<=0) exit (0);
	if (fork () > 0) {
		sprintf (str, "echo 1 - run with i=%d", i);
		system (str);
		sprintf (str, "%d", i-1);
		execlp (argv[0], argv[0], str, NULL);
	}
	else {
		sprintf (str, "echo 2 - run with i=%d", i);
		system (str);
		sprintf (str, "%d", i-2);
		execlp (argv[0], argv[0], str, NULL);
	}
	printf("PID=%d se mi stampa c'è un problema\n", getpid());
	exit (0);
}

