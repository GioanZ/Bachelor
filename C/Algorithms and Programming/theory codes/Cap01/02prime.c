#include <stdio.h>
#include <math.h>

int Prime(int n);
int PrimeOpt(int n);

int main() {
  int n;
  printf("Input number:  ");
  scanf("%d", &n);
  printf("Basic algorithm\n");
  if (Prime(n)== 0)
    printf("%d is not prime.\n", n);
  else
    printf("%d is prime.\n", n);
  printf("Optimized algorithm\n");
  if (PrimeOpt(n)== 0)
    printf("%d is not prime.\n", n);
  else
    printf("%d is prime.\n", n);
  return 0;
}
int Prime(int n) {
  int fact;
  if (n == 1)
    return 0;
  fact =2;
  while (n%fact != 0)
    fact  = fact +1;
  return (fact == n);
}

int PrimeOpt(int n) {
  int fact;
  if (n == 1)
    return 0;
  fact = 2;
  while (fact <= sqrt(n)) {
    if (n % fact == 0)
      return 0;
	fact  = fact +1;
  }
  return 1;
}
