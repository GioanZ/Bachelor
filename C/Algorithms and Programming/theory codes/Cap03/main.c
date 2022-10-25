#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Item.h"
#include "IterativeSorting.h"
#define DBG 1
#define MAX 100

int main(int argc, char *argv[]) {
  int i=0, upperbound = 0, k, N, sw, c[MAX];
  Item a[MAX], b[MAX];

  if (argc !=3) {
    printf("Error in command line, correct format: \n");
    printf("client <number of keys> <1 for random input, 0 for for input from keyboard\n");
    exit(1);
  }

  N = atoi(argv[1]);
  if (N>MAX) {
    printf("Maximum number of elements exceeded\n");
    return 1;
  }


  sw = atoi(argv[2]);

  if (sw) {
    printf("Filling in the array with random values\n");
    srand(time(NULL));
    for (i = 0; i < N; i++) {
      a[i] = ITEMrand();
      if (a[i] > upperbound)
        upperbound = a[i];
    }
  }
  else {
    printf("Input array values (key is >=0) \n");
    for (i = 0; i < N; i++) {
      a[i] = ITEMscan();
      if (a[i] > upperbound)
        upperbound = a[i];
    }
    printf("\n");
  }
  k = upperbound +1;

#if DBG
  printf("The original array is\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");
#endif

  printf("\nIterative Sorting Algorithms\n");
  printf("===============\n");
  printf("1. Bubble sort\n");
  printf("2. Optimized bubble sort\n");
  printf("3. Selection sort\n");
  printf("4. Insertion sort\n");
  printf("5. Shell sort\n");
  printf("6. Counting sort\n");
  printf("7. Exit\n");
  printf("Enter your choice : ");
  if(scanf("%d",&i)<=0) {
    printf("Integers only!\n");
    exit(0);
  }
  else {
    switch(i) {
      case 1:     BubbleSort(a, N);
                  break;
      case 2:     OptBubbleSort(a, N);
                  break;
      case 3:     SelectionSort(a, N);
                  break;
      case 4:     InsertionSort(a, N);
                  break;
      case 5:     ShellSort(a, N);
                  break;
      case 6:     CountingSort(a, b, c, N, k);
                  break;
      case 7:     break;
      default:    printf("Invalid option\n");
    }
  }
  printf("Array a sorted in ascending order for key x is:\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");
  return 0;
}
