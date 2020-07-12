typedef struct Jogador Jogador;

#ifndef JOGADOR_H
#define JOGADOR_H

#include "tabuleiro.h"

#define LADR_MAO 6

typedef struct Jogador {
  
  char nome[16];
  int pontTotal;
  int ladrMao;
  Ladrilho ladr[LADR_MAO];
  
} Jogador;

#endif