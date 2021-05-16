#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "tabuleiro.h"
#include "erros.h"
#include "gerenciador.h"
#include "util.h"
#include "jogador.h"
#include "help.h"

int main(void) {
  
  Gerenciador g;
  g.listJog = NULL;
  g.tab.matriz = NULL;
  g.estado = JOGO_PARADO;

  while(g.estado == JOGO_PARADO || g.estado == EM_JOGO){

    if(g.estado == EM_JOGO){
      printJogo(g);
      escolherComando(&g); 
    } else {
      printPreJogo(g);
      escolherComando(&g);
    }
  }

  encerrarGerenciador(&g);
  
} 


