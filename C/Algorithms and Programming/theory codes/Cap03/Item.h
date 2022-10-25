#include <stdio.h>
#include <stdlib.h>
#define maxKey 99

typedef int Item;

int  ITEMeq(Item A, Item B);
int  ITEMneq(Item A, Item B);
int  ITEMlt(Item A, Item B);
int  ITEMgt(Item A, Item B);
Item ITEMscan();
void ITEMshow(Item A);
Item ITEMrand();

