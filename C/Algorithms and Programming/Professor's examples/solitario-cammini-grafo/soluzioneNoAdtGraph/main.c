/*
 *  Tema d'esame del 01/02/2010
 *  Solitario giocato su un grafo. Dato un grafo orientato pesato, occorre:
 *  1) visualizzarne l'elenco di archi in ordine alfabetico
 *  2) trovare un cammino semplice sul quale i nodi, complessivamente, 
 *     forniscano tutte le categorie di "premi"
 *  3) trovare un cammino che permetta di raggiungere il punteggio (somma 
 *     dei pesi degli archi attraversati e degli eventuali "premi" acquisiti 
 *     sui nodi) massimo.
 *
 *  Il grafo viene rappresentato utilizzando un grafo ad hoc nel client
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "st.h"


#define MAX 6

/********************************************************************
  Strutture dati utilizzate
********************************************************************/

typedef struct premio premio_t;
typedef struct myGraph *MyGraph;
typedef struct nodo nodo_t;
typedef struct listnode *link;
struct listnode { int v; int wt; link next; } ;
typedef struct { int v; int w; int wt;} Edge;

struct myGraph {
  int V, E, C;
  ST stVertici;
  ST stCategorie;
  nodo_t *nodi;
};

/* struttura per la descrizione dei nodi */
struct nodo {
  char *nome;
  link adj;
  int numPremi;
  premio_t *listaPremi;
  int visitato;
};

/* struttura per la descrizione degli archi */
struct premio {
  int valore;
  int categoria;
  int usato;
  premio_t *next;
};

/********************************************************************
  Prototipi
********************************************************************/

Edge EDGE(int, int, int);

void  MyGraphInsertE(MyGraph G, Edge e);
MyGraph leggi(char *nomeFile);
int cammino_semplice(MyGraph grafo, int *premi, int *cammino, 
                     int i, int mossa);
int tutti_premi(int *premi, int nc);
int cammino_ottimo(MyGraph grafo, int *premi, int i,
                   int mossa, int score, int best);
int confrontaArchi(MyGraph grafo, Edge e1, Edge e2);
Edge *ordinaArchi(MyGraph grafo);
void libera(MyGraph grafo);

/********************************************************************
  Main
********************************************************************/
int main(void)
{
  int i, cmd, src, dst, lunghezza, best, *cammino, *premi;
  char nome[100];
  Edge *archiInOrdine;
  MyGraph grafo;

  printf("File con la descrizione del grafo? ");
  scanf("%s", nome);
  printf("%s\n", nome);

  grafo = leggi(nome);

  do {
    printf("Funzioni:\n");
    printf("  0. terminazione programma\n");
    printf("  1. elenco ordinato degli archi\n");
    printf("  2. cammmino con nodi associati a tutti i premi\n");
    printf("  3. cammmino di punteggio massimo\n");
    printf("Comando: ");
    scanf("%d", &cmd);
    
    switch (cmd) {
    case 0: break;
    case 1:
      printf("Elenco degli archi:\n");
      archiInOrdine = ordinaArchi(grafo);
      for (i=0; i<grafo->E; i++) {
        src = archiInOrdine[i].v;
        dst = archiInOrdine[i].w;
        printf("%s %s\n", grafo->nodi[src].nome, grafo->nodi[dst].nome);
      }
      free(archiInOrdine);
      printf("\n");
      break;
    case 2:
      cammino = (int *)malloc(grafo->V*sizeof(int));
      premi = (int *)malloc(grafo->C*sizeof(int));
      for (i=0;i<grafo->C;i++) premi[i]=0;
      printf("Vertice di partenza: ");
      scanf("%s", nome);
      src = STsearch(grafo->stVertici, nome);
      lunghezza = cammino_semplice(grafo, premi, cammino, src, 0);
      if (lunghezza >= 0) {
        printf("Cammino trovato: ");
        for (i=0; i<=lunghezza; i++) {
          dst = cammino[i];
          printf("%s%s", grafo->nodi[dst].nome, i<lunghezza ? " - " : "");
        }
        printf("\n\n");
      } else {
        printf("Il cammino cercato non esiste!\n");
      }
      free(cammino); free(premi);
            break;
        case 3:
      premi = (int *)malloc(grafo->C*sizeof(int));
      for (i=0;i<grafo->C;i++) premi[i]=0;
      printf("Vertice di partenza: ");
      scanf("%s", nome);
      src = STsearch(grafo->stVertici, nome);
      best = cammino_ottimo(grafo, premi, src, 0, 0, 0);
      printf("Il massimo punteggio ottenibile in ");
      printf("%d mosse e' %d\n\n", MAX, best);
      free(premi);
      break;
    }
  } while (cmd != 0);

  libera(grafo);

  return EXIT_SUCCESS;
}

Edge EDGE(int v, int w, int wt)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

link NEW(int v, int wt, link next)
{
    link x = malloc(sizeof *x);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

/********************************************************************
  Funzione di lettura del file delle librerie
********************************************************************/
void  MyGraphInsertE(MyGraph G, Edge e)
{
    int v = e.v, w = e.w, wt = e.wt;
    if (v == w) return;
    G->nodi[v].adj = NEW(w, wt, G->nodi[v].adj);
    G->E++;
}

/********************************************************************
  Funzione di lettura del file delle librerie
********************************************************************/
MyGraph leggi(char *nomeFile)
{
  char nome[100], nome1[100];
  int nv, ne, nc, i, k, src, dst, ew, cat, valore, iCat;
  FILE *fp;
  MyGraph grafo;

  fp = fopen(nomeFile, "r");
  fscanf(fp, "%d%d%d", &nv, &ne, &nc);

  grafo = (MyGraph) malloc (sizeof(struct myGraph));

  grafo->V = nv;
  grafo->E = 0;
  grafo->C = nc;
  grafo->stVertici = STinit(nv);
  grafo->stCategorie = STinit(nc);
  grafo->nodi = (nodo_t *)malloc(nv*sizeof(nodo_t));
  for (i = 0; i < nv; i++)
    grafo->nodi[i].adj = NULL;

  /* vertici */
  for (i=0; i<nv; i++) {
    fscanf(fp, "%s", nome);
    /* inserisco nel vettore ordinatamente */
    STinsert(grafo->stVertici,nome,i);
    grafo->nodi[i].listaPremi = NULL;
    grafo->nodi[i].numPremi = 0;
    grafo->nodi[i].visitato = 0;
    grafo->nodi[i].nome = strdup(nome);
  }

  /* archi */
  for (k=0; k<ne; k++) {
    fscanf(fp, "%s %s %d", nome, nome1, &ew);
    src = STsearch(grafo->stVertici, nome);
    dst = STsearch(grafo->stVertici, nome1);
    MyGraphInsertE(grafo, EDGE(src, dst, ew));
  }

  /* premi */
  iCat=0;
  while (fscanf(fp, "%s %s %d", nome, nome1, &valore) == 3) {
    premio_t *p;
    src = STsearch(grafo->stVertici, nome);
    cat = STsearch(grafo->stCategorie, nome1);
    if (cat<0) {
      cat = STinsert(grafo->stCategorie, nome1, iCat++);
    }
    p = malloc(sizeof *p);
    p->valore = valore;
    p->categoria = cat;
    p->usato = 0;
    /* inserimento in testa alla lista dei premi */
    p->next = grafo->nodi[src].listaPremi;
    grafo->nodi[src].listaPremi = p;
    grafo->nodi[src].numPremi++;
  }

  fclose(fp);

  return grafo;
}

/********************************************************************
  Funzione di confronto tra archi
********************************************************************/
int confrontaArchi(MyGraph grafo, Edge e1, Edge e2)
{
  if (e1.v != e2.v) {
    /* se vertici di partenza diversi, usa i loro nomi */
    return strcmp(grafo->nodi[e1.v].nome,grafo->nodi[e2.v].nome);
  }
  /* vertici di partenza uguali, usa i vertici di arrivo */
  return strcmp(grafo->nodi[e1.w].nome,grafo->nodi[e2.w].nome);
}

/********************************************************************
  Funzione di ordinamento
********************************************************************/
Edge *ordinaArchi(MyGraph grafo)
{
  int i, j, v;
  Edge e;
  Edge *archi = (Edge *)malloc(grafo->E*sizeof(Edge));

  for (v=i=0; v<grafo->V; v++) {
      link pe;
      for (pe=grafo->nodi[v].adj; pe!=NULL; pe=pe->next) {
        archi[i++] = EDGE(v,pe->v,pe->wt);
      }
  }
    
  /* insertion sort */
  for (i=1; i<grafo->E; i++) {
    e = archi[i];
    j = i-1;
    while (j>=0 && confrontaArchi(grafo,e,archi[j])<0) {
      archi[j+1] = archi[j];
      j--;
    }
    archi[j+1] = e;
  }
  return archi;
}

/********************************************************************
  Funzione che libera memoria
********************************************************************/
void libera(MyGraph grafo)
{
  STfree(grafo->stVertici);
  STfree(grafo->stCategorie);
  free(grafo->nodi);
  free(grafo);
}

/********************************************************************
  Funzione di ricerca di un cammino semplice tale che i nodi che 
  lo compongono abbiano associati (complessivamente) premi di tutte 
  le categorie
********************************************************************/
int cammino_semplice(MyGraph grafo, int *premi, int *cammino, 
                     int i, int mossa)
{
  int dst, lunghezza;
  premio_t *p;
  link e;
  
  if (grafo->nodi[i].visitato != 0) {
    /* nodo gia' toccato */
    return -1;
  }
  cammino[mossa] = i;
  
  /* prendo gli eventuali premi nel nodo corrente */
  for (p=grafo->nodi[i].listaPremi; p!=NULL; p=p->next) {
    premi[p->categoria]++;
  }
  if (tutti_premi(premi, grafo->C)) {
    /* ok: cammino trovato */
    return mossa;
  }
  
  grafo->nodi[i].visitato = 1;

  /* provo gli archi uscenti */
  for (e=grafo->nodi[i].adj; e!=NULL; e=e->next) {
    dst = e->v;
    lunghezza = cammino_semplice(grafo, premi, cammino, dst, mossa+1);
    if (lunghezza >= 0) {
      grafo->nodi[i].visitato = 0;
      return lunghezza;
    }
  }
  
  /* backtrack */
  for (p=grafo->nodi[i].listaPremi; p!=NULL; p=p->next) {
    premi[p->categoria]--;
  }
  grafo->nodi[i].visitato = 0;

  return -1;
}

/********************************************************************
  Funzione che verifica di aver preso tutti le categorie di premi
********************************************************************/
int tutti_premi(int *premi, int nc)
{
  int i;
  
  for (i=0; i<nc; i++) {
    if (premi[i] == 0) {
      return 0;
    }
  }
  return 1;
}

/********************************************************************
  Funzione di ricerca di un cammino ottimo che permette al giocatore
  di totalizzare il massimo punteggio possibile
********************************************************************/
int cammino_ottimo(MyGraph grafo, int *premi, int i,
                   int mossa, int score, int best)
{
  int dst, premio, nArchi, val;
  premio_t *p;
  link e;
  
  /* terminazione */
  if (grafo->nodi[i].numPremi<0 || score<0 || mossa>MAX) {
    /* nodo gia' toccato/esaurito o punteggio negativo */
    return best;
  }
  
  /* il valore raddoppia quando tutti_premi ritorna 1 */
  val = score * (1+tutti_premi(premi, grafo->C));
  best = val > best ? val : best;
  
  /* passo ricorsivo */
  if (grafo->nodi[i].numPremi > 0) {
    /* uno o piu' premi disponibili: ricorsione sui premi e gli archi */ 
    grafo->nodi[i].numPremi--;
    for (p=grafo->nodi[i].listaPremi; p!=NULL; p=p->next) {
      if (p->usato == 0) {
        premi[p->categoria]++;
        p->usato = 1;
        score += p->valore;
        val = score * (1+tutti_premi(premi, grafo->C));
        best = val > best ? val : best;

	for (e=grafo->nodi[i].adj; e!=NULL; e=e->next) {
	  dst = e->v;
          score += e->wt;
          best = cammino_ottimo(grafo, premi, dst, mossa+1, score, best);
          score -= e->wt;
        }

        score -= p->valore;
        premi[p->categoria]--;
        p->usato = 0;
      }
    }
    grafo->nodi[i].numPremi++;
  } else {
    /* nessun premio: provo solo a percorrere tutti gli archi */ 
    for (e=grafo->nodi[i].adj; e!=NULL; e=e->next) {
        dst = e->v;
        score += e->wt;
      best = cammino_ottimo(grafo, premi, dst, mossa+1, score, best);
      score -= e->wt;
    }
  }

  return best;
}
