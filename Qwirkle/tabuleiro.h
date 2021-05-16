typedef struct Ladrilho Ladrilho;
typedef struct Tabuleiro Tabuleiro;

#ifndef TABULEIRO_H
#define TABULEIRO_H


#define DIM       217
#define QNT_PECAS 108

typedef struct Ladrilho {

  char tipo;
  int cor;

} Ladrilho;

typedef struct Tabuleiro {

  Ladrilho **matriz;

  int ladrDisp; 
  Ladrilho *ladr;  // vetor para armazenar as peças disponiveis

  int lSup;
  int lInf;
  int cEsq;
  int cDir;

} Tabuleiro;

Ladrilho LADR_VAZIO();
int cmpLadr(Ladrilho ladr1, Ladrilho ladr2);

void ordenarListLadr(Ladrilho *list, int qnt);

int iniciarTabuleiro(Tabuleiro *tab);
void liberarTabuleiro(Tabuleiro *tab); 

int convCoordMatrizJogo(int coord);
int convCoordJogoMatriz(int coord);

#endif
