typedef struct c_t {
  int c;
  int d;
  struct c_t *next, *prev;
} col;

typedef struct r_t {
  col *head, *tail;
  int nEl;
} riga;

typedef struct m_t {
  riga *righe;
  int R;
} mat;

typedef mat matr_t;

col *creaCol(int c, int d, col *next, col *prev) {
  col *nc = calloc(1, sizeof(col));
  nc->c = c;
  nc->d = d;
  nc->prev = prev;
  nc->next = next;
  return nc;
}

void aggiornaMat(matr_t *m, int d, int r, int c) {
  if (m == NULL || r >= m->R) return;
  if (d == 0) {
    col *iterC = m->righe[r].head;
    if (iterC == NULL) return;
    while(iterC != NULL && iterC->c < c) iterC = iterC->next;
    if (iterC != NULL && iterC->c == c) {
      if (iterC->prev != NULL)
        iterC->prev->next = iterC->next;
      else
        m->righe[r].head = iterC->next;
      if (iterC->next != NULL)
        iterC->next->prev = iterC->prev;
      else
        m->righe[r].tail = iterC->prev;
      free(iterC);
      m->righe[r].nEl--;
    }
    return;
  }
  if (d != 0) {
    col *iterC = m->righe[r].head;
    if (iterC == NULL) {
      m->righe[r].head = m->righe[r].tail = creaCol(c, d, NULL, NULL);
      m->righe[r].nEl++;
      return;
    }
    while(iterC != NULL && iterC->c < c) iterC = iterC->next;
    if (iterC != NULL && iterC->c == c) {
      iterC->d = d;
    } else if (iterC == m->righe[r].head) {
      col *nc = creaCol(c, d, m->righe[r].head, NULL);
      m->righe[r].head->prev = nc;
      m->righe[r].head = nc;
    } else if (iterC == NULL) {
      col *nc = creaCol(c, d, NULL, m->righe[r].tail);
      m->righe[r].tail->next = nc;
      m->righe[r].tail = nc;
      return;
    } else {
      col *nc = creaCol(c, d, iterC, iterC->prev);
      iterC->prev->next = nc;
      iterC->prev = nc;
    }
    m->righe[r].nEl++;
  }
}

matr_t *creaMat(int R) {
  int i;
  matr_t *m = calloc(1, sizeof(mat));
  m->righe = calloc(R, sizeof(riga));
  m->R = R;
  for(i=0;i<R;i++) {
    m->righe[i].head = m->righe[i].tail = NULL;
    m->righe[i].nEl = 0;
  }
  return m;
}

void stampaMat(matr_t *m) {
  int r;
  printf("\n\tMatrice \n");
  for(r=0;r<m->R;r++) {
    col *iterC = m->righe[r].head;
    printf("Riga %d > ", r);
    while(iterC != NULL) {
      printf("<%d, %d> ", iterC->c, iterC->d);
      iterC = iterC->next;
    }
    printf("\n");
  }
}
