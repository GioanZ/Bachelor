#include <stdio.h>
#include <string.h>

#define MAXR 19
#define MAXC 19

typedef struct mossa_s {
    int r;
    int c;
    int sospendi;
} mossa_t;

typedef struct dir_s {
    int dx;
    int dy;
} dir_t;

mossa_t leggiMossa(char tab[MAXR][MAXC+1], char colore, int nr, int nc);
int controllaMossa (char tab[MAXR][MAXC+1], mossa_t mossa, int nr, int nc);
int contaPedineDirezione(char t[MAXR][MAXC+1], mossa_t mossa, dir_t direzione, int nr, int nc);
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1], int nr, int nc);

int main (int argc, char *argv[])
{
    char tab[MAXR][MAXC+1];
    mossa_t mossa;
    FILE *fp;
    int i,j,r,c,cnt,finito=0, ok, nr, nc;
        
    fp = fopen(argv[1],"r");


    for (i=0; i<MAXR; i++) {
        if (fscanf(fp,"%s",tab[i])==EOF) {
            break;
        }
        nc = strlen(tab[i]);
    }
    nr = i;
    fclose(fp);
    
    while (!finito) {
        
        stampaTabella(stdout,tab,nr,nc);
        /* black */
        mossa = leggiMossa(tab,'N',nr,nc);
        if (mossa.sospendi)
            break;
        finito = controllaMossa(tab,mossa,nr,nc);
        if (finito) {
            printf("vittoria del nero\n");
        }
        else {
            /* white */
            mossa = leggiMossa(tab,'B',nr,nc);
            if (mossa.sospendi)
                break;
            finito = controllaMossa(tab,mossa,nr,nc);
            if (finito) {
                printf("vittoria del bianco\n");
            }
        }
    }
    
    if (argc > 2) {
        printf("partita salvata su: %s\n", argv[2]);
        fp = fopen(argv[2],"w");
        stampaTabella(fp,tab,nr,nc);
        fclose(fp);
    }
    
}

mossa_t leggiMossa(char t[MAXR][MAXC+1], char colore, int nr, int nc)
{
    int r, c, ok;
    mossa_t m = {0,0,0};
    do {
        if (colore=='B') printf("Mossa del bianco: ");
        else printf("Mossa del nero: ");
        scanf("%d%d",&r,&c);
        if (r==0 && c==0) {
            m.sospendi = 1;
            return m;
        }
        r--; c--;
        if (r<0 || r>=nr || c<0 || c>=nc || t[r][c]!='.') {
            printf("mossa non valida. ripetere.\n");
            ok = 0;
        }
        else {
            t[r][c] = colore;
            ok = 1;
        }
    } while (!ok);
    m.r = r;
    m.c = c;
    return m;
}


int contaPedineDirezione(char t[MAXR][MAXC+1], mossa_t mossa, dir_t direzione, int nr, int nc) {
  
    int r, c, cnt, i, j, vittoria, dx, dy, col;
    
    r = mossa.r;
    c = mossa.c;
    col = t[r][c];

    vittoria = 0;
    
    dx = direzione.dx;
    dy = direzione.dy;

    for (i =r-dx,j=c-dy,cnt=1;
         i>=0 && j>=0 && i<nr && j<nc && t[i][j]==col;
         i-=dx,j-=dy)
        cnt++;
    for (i =r+dx,j=c+dy;
         i>=0 && j>=0 && i<nr && j<nc && t[i][j]==col;
         i+=dx,j+=dy)
        cnt++;
    
    return cnt;
    
    
}


int controllaMossa (char t[MAXR][MAXC+1], mossa_t mossa, int nr, int nc)
{
    int r, c, cnt, i, j, k, vittoria, dx, dy;

    dir_t delta[4] = {
      {0,1},
      {1,0},
      {1,1},
      {1,-1},
    };

    /* if no check is successful it will remain at 0 */
    vittoria = 0;

    for (k=0; k<4 && !vittoria; k++)
        vittoria = (contaPedineDirezione(t, mossa, delta[k], nr, nc) >= 5);
    
    return vittoria;
}

/* table */
void stampaTabella(FILE *fp, char tab[MAXR][MAXC+1], int nr, int nc)
{
    int i, j;
    
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++)
            fprintf(fp,"%c",tab[i][j]);
        fprintf(fp,"\n");
    }
}
