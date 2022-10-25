#include "Item.h"
#include "IterativeSorting.h"

void BubbleSort(Item A[], int N) {
  int i, j, l=0, r=N-1;
  Item temp;

  for(i = l; i < r; i++) {
    for (j = l; j <  r - i + l; j++) {
	  if (ITEMgt(A[j], A[j+1])) {
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
    }
  }

  return;
}

void OptBubbleSort(Item A[], int N) {
  int i, j, l=0, r=N-1, flag;
  Item temp;

  flag = 1;
  for(i = l; i < r && flag == 1; i++) {
    flag = 0;
    for (j = l; j < r - i + l; j++)
      if (ITEMgt(A[j],A[j+1])) {
        flag = 1;
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
  }
  return;
}

void SelectionSort(Item A[], int N) {
  int i, j, l=0, r=N-1, min;
  Item temp;
  for(i = l; i < r; i++) {
    min = i;
	for (j = i + 1; j <= r; j++)
      if (ITEMlt(A[j],A[min]))
        min = j;
    if (min !=i) {
      temp = A[i];
      A[i] = A[min];
      A[min] = temp;
    }
  }
  return;
}

void InsertionSort(Item A[], int N) {
  int i, j, l=0, r=N-1;
  Item x;
  for(i = l+1; i <= r; i++) {
    x = A[i];
    j = i - 1;
    while (j >= l && ITEMlt(x, A[j])) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = x;
  }
}

void ShellSort(Item A[], int N) {
  int i, j, h=1, l=0, r= N-1;
  Item tmp;

  while (h < N/3)
    h = 3*h+1;
  while(h >= 1) {
    for (i = l + h; i <= r; i++) {
      j = i;
      tmp = A[i];
      while(j >= l + h  && ITEMlt(tmp,  A[j-h])) {
        A[j] = A[j-h];
        j -=h;
      }
      A[j] = tmp;
    }
    printf("h = %d, h-sorted array is: \n", h);
    for (i = 0; i <(r-l+1); i++)
      ITEMshow(A[i]);
    printf("\n");
    h = h/3;
  }
}

void CountingSort(Item A[], Item B[], int C[], int N, int k) {
  int i, l=0, r=N-1;

  for (i = 0; i < k; i++)
    C[i] = 0;

  for (i = l; i <= r; i++)
    C[A[i]]++;

  for (i = 1; i < k; i++)
    C[i] += C[i-1];

  for (i = r; i >= l; i--) {
    B[C[A[i]]-1] = A[i];
    C[A[i]]--;
  }

  for (i = l; i <= r; i++)
    A[i] = B[i];
}

