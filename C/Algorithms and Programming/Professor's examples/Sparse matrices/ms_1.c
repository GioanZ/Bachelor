#include <stdio.h>
#include <stdlib.h>

typedef struct elem_s {
  int col;
  int val;
} elem;

typedef struct riga_s {
  int cont;
  elem *el;
} riga;

riga *creaMat(int **m , int r, int c) {
  int i, j, count = 0;
  riga *s = (riga *) malloc(r * sizeof(riga));
  if (s == NULL)
    exit(-1);
  for(i=0; i<r; i++) {
    // Count how many elements are non-null in each row and then allocate accordingly
    count = 0;
    for(j=0; j<c; j++) {
      if (m[i][j])
        count++;
    }
    s[i].el = (elem*) malloc(count * sizeof(elem));
    if (s[i].el == NULL)
      exit(-1);
    s[i].cont = count;
    count = 0;
    // Enter only non-null elements
    for(j=0; j<c; j++) {
      if (m[i][j]) {
        s[i].el[count].col = j;
        s[i].el[count++].val = m[i][j];
      }
    }
  }
  return s;
}

int accediMat(riga *s, int r, int c, int x, int y) {
  int i;
  if (x >= r || y >= c || x < 0 || y < 0)
    return 0;
  for(i=0; i<s[x].cont; i++) {
    if (s[x].el[i].col == y)
      return s[x].el[i].val;
    // If I exceeded the desired index
    if (s[x].el[i].col > y)
      return 0;
  }
  return 0;
}
