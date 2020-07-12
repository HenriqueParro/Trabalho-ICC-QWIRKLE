#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "erros.h"

/*
* Funcao que gera e retorna um Ladrilho padronizado como VAZIO.
*/
Ladrilho LADR_VAZIO(){

  Ladrilho l;
  l.tipo = ' ';
  l.cor = 0;

  return l;
}

/*
* Funcao que compara se dois ladrilhos sao iguais ou nao.
*/
int cmpLadr(Ladrilho ladr1, Ladrilho ladr2){

  if(ladr1.tipo == ladr2.tipo && ladr1.cor == ladr2.cor) return TRUE;
  return FALSE;
}

/*
*   Ordenar as pecas de uma lista de ladrilhos.
*/
void ordenarListLadr(Ladrilho *list, int qnt){

    for(int i = 0; i < qnt - 1; i++){
        for(int j = 0; j < qnt - 1; j++){
            Ladrilho aux;
            if(cmpLadr(list[j], LADR_VAZIO()) == TRUE){
                aux = list[j + 1];
                list[j + 1] = list[j];
                list[j] = aux;
            }
        }
    }
}

/*
*   Esta funcao randomiza as pecas do vetor de ladrilhos
*/
void embaralharLadr(Ladrilho *vetor, int tamanhoVetor){

  unsigned static int r;
  srand(time(NULL) + r);
  r++;
  
	for (int i = 0; i < tamanhoVetor; i++){
		int r = rand() % tamanhoVetor;

		Ladrilho temp = vetor[i];
		vetor[i] = vetor[r];
		vetor[r] = temp;
	}
}

/*
*   Inicializacao dos campos do tabuleiro com  a devida alocacao de memoria
*/
int iniciarTabuleiro(Tabuleiro *tab){

  tab->ladr = (Ladrilho*) malloc(QNT_PECAS*sizeof(Ladrilho));
  if(tab->ladr == NULL) return erro(ERRO_MEMORIA);

  tab->matriz = (Ladrilho**) malloc(DIM*sizeof(Ladrilho*));
  if(tab->matriz == NULL){
    free(tab->ladr);
    return erro(ERRO_MEMORIA);
  }

  for(int i = 0; i < DIM; i++){

    tab->matriz[i] = (Ladrilho*) malloc(DIM*sizeof(Ladrilho));
    if(tab->matriz[i] == NULL){
      for(int j = i; j >= 0; j--) free(tab->matriz[i]);
      free(tab->matriz);
      free(tab->ladr);
      return erro(ERRO_MEMORIA);
    }
  }

  for(int i = 0; i < DIM; i++){
    for(int j = 0; j < DIM; j++) tab->matriz[i][j] = LADR_VAZIO();
  }

  for(int i = 0; i < QNT_PECAS; i++){
    tab->ladr[i].tipo = 'A' + i/18;
    tab->ladr[i].cor = 1 + (i % 6);
  }

  tab->ladrDisp = QNT_PECAS;

  embaralharLadr(tab->ladr, tab->ladrDisp);

  tab->lSup = 0;
  tab->lInf = 0;
  tab->cEsq = 0;
  tab->cDir = 0;

  return erro(SUCESSO);
}


/*
*   Libera a memoria alocada pelo tabluleiro
*/
void liberarTabuleiro(Tabuleiro *tabuleiro){

    for(int i = 0; i < DIM; i++) free(tabuleiro->matriz[i]);
    free(tabuleiro->matriz);
    free(tabuleiro->ladr);
}
/*
*   Funcao que converte as coordenadas da matriz para as coordenadas do tabuleiro(jogo).
*/
int convCoordMatrizJogo(int coord){
    
  int c = coord - (DIM-1)/2;
  return c;
}

/*
*   Funcao que converte as coordenadas do tabuleiro(jogo) para as coordenadas da matriz.
*/
int convCoordJogoMatriz(int coord){

    int c = (DIM-1)/2 + coord;
    return c;
}


