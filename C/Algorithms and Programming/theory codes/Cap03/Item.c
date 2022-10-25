#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

int ITEMeq(Item A, Item B) {
  return (A == B);
}

int ITEMneq(Item A, Item B) {
  return (A != B);
}

int ITEMlt(Item A, Item B) {
  return (A < B);
}

int ITEMgt(Item A, Item B) {
  return (A > B);
}

Item ITEMscan() {
  Item A;
  printf("item = ");
  scanf("%d", &A);
  return A;
}

void ITEMshow(Item A) {
  printf("%6d \n", A);
}

Item ITEMrand() {
  Item A = maxKey*rand()/RAND_MAX;
  return A;
}
