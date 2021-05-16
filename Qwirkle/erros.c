#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "erros.h"
#include "interface.h"

int ultErro = SUCESSO;

/*
* Funcao que atualiza o valor da variavel global ultErro.
*/
int erro(int erro){
  ultErro = erro;
  return erro;
}

/*
* Funcao que retorna o valor da variavel global ultErro.
*/
int getUltErro(){
  return ultErro;
}
