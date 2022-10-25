#include <stdio.h>
#define N 5

int LinearSearch(int v[], int l, int r, int k);
int LinearSearch2(int v[], int l, int r, int k);

int main(){
  int i, k, v[N];

  for (i=0; i<N; i++) {
    printf("Input v[%d]:", i);
    scanf("%d", &v[i]);
  }
  printf("Input key:  ");
  scanf("%d", &k);
  i = LinearSearch(v, 0, N-1, k);
  if (i != -1)
    printf("Key found at index: %d\n", i);
  else
    printf("Key not found\n");
  return 0;
}

int LinearSearch(int v[], int l, int r, int k) {
  int i=l;
  int found=0;

  while (i<=r && found == 0)
    if (k == v[i])
      found =1;
    else
     i++;
   if (found ==0)
     return -1;
   else
     return i;
}
