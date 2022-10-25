#include <stdio.h>
#define N 11
#define DBG 1

int main() {
int i, j, p, q, id[N], sz[N];
  for(i=0; i<N; i++) {
    id[i] = i;
    sz[i] =1;
  }

  printf("Input pair p q:  ");
  while (scanf("%d %d", &p, &q) ==2) {
    for (i = p; i!= id[i]; i = id[i]);
    for (j = q; j!= id[j]; j = id[j]);
    if (i == j)
      printf("pair %d %d already connected\n", p,q);
    else {
      printf("pair %d %d not yet connected\n", p, q);
      if (sz[i] <= sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
      }
	  else {
        id[j] = i;
        sz[i] += sz[j];
      }
#if DBG
    printf("Now array id contains:\n");
    for(i=0; i<N; i++)
      printf("%d ", id[i]);
    printf("\n\n");
#endif
    }
    printf("Input pair p q:  ");
  }
  return 0;
}
