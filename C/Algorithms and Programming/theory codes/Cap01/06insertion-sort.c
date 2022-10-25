#include <stdio.h>

#define MAX 10000

void InsertionSort(int A[], int N);

int main() {
  int i, N, A[MAX];

  printf("Input array size (max 10000):  ");
  scanf("%d", &N);

  for (i = 0; i <N; i++) {
    printf("Input value A[%d]:  ", i);
    scanf("%d", &A[i]);
  }

  InsertionSort(A, N);

  printf("A sorted in ascending order is:\n");
  for (i = 0; i <N; i++)
    printf("A[%d] = %d\n", i, A[i]);

  return 0;
}
void InsertionSort(int A[], int N) {
  int i, j, l=0, r=N-1, x;
  for(i = l; i <= r; i++) {
    x = A[i];
    j = i - 1;
	while (j >= l && x < A[j]) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = x;
  }
}
