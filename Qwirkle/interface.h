#ifndef INTERFACE_H
#define INTERFACE_H

#include "tabuleiro.h"
#include "gerenciador.h"
#include "jogador.h"

#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_GRAY     "\033[47m"
#define BG_END      "\033[0m"

enum Cor {RED = 1, GREEN, YELLOW, BLUE, MAGENTA, CYAN, GRAY} Cor;

void limparTela();
void printLogo();
void printErro();
void printLadrilho(Ladrilho ladrilho);
void printTabuleiro(Tabuleiro tab);
void printPecasJogador(Jogador jog);
void printJogo(Gerenciador g);
void printPreJogo(Gerenciador g);

#endif