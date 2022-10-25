#include <stdio.h>
#include <stdlib.h>

#define N 8

int BinSearch(int v[], int l, int r, int k);

int main(){
  int i, k, v[N];

  for (i=0; i<N; i++) {
    printf("Input v[%d]:", i);
    scanf("%d", &v[i]);
  }
  printf("Input key:  ");
  scanf("%d", &k);
  i = BinSearch(v, 0, N-1, k);
  if (i != -1)
    printf("Key found at index: %d\n", i);
  else
    printf("Key not found\n");
  return 0;
}


int BinSearch(int v[], int l, int r, int k) {
  int m, found;

  while(l<=r) {
    m =  (l+r)/2;
    if(v[m] == k)
      return(m);
    if(v[m] < k)
      l = m+1;
    else
      r = m-1;
  }
  return -1;
}
