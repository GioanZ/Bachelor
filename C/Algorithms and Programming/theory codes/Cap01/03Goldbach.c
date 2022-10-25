#include <stdio.h>
#define upper 20

int Prime (int n);

void Goldbach(void);

int main() {
  printf("Is there any counterexample to Goldbach's conjecture?\n");
  Goldbach();
  return 0;
}
int Prime(int n) {
  int factor;
  if (n == 1)
    return 0;
  factor =2;
  while (n%factor != 0)
    factor  = factor +1;
  return (factor == n);
}

void Goldbach(void) {
  int n, counterexample, p, q;
  n = 2;
  do {
    n = n + 2;
	printf("I try for n = %d\n", n);
	counterexample = 1;
	for (p = 2; p <= n-2; p++) {
      q = n -p;
      if (Prime(p) == 1 && Prime(q) == 1) {
        counterexample = 0;
        printf("%d %d\n", p, q);
      }
    }
  }
  while (counterexample == 0 && n < upper);
  if (counterexample == 1)
    printf("A counterexample to Goldabch's conjecture is: %d \n", n);
  else
    printf("Until n= %d I could not find any counterexample to Goldbach's conjecture\n", upper);
  return ;
}
