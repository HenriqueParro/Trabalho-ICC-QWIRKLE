#include <stdio.h>
#include <string.h>

#include "help.h"
#include "interface.h"
#include "util.h"
#include "erros.h"
#include "tabuleiro.h"

int pag = 1;

void proxPag(){
  if(pag < 6) pag++;
}

void voltarPag(){
  if(pag > 1) pag--;
}

void printPrimPag(){
  
  limparTela();
  printLogo();

  printf("\nREGRAS BASICAS:\n\n");
  printf("- Existem 108 ladrilhos no tabuleiro, com um limite maximo de 6 pecas por jogador, comportando portanto ate 18 jogadores.\n\n");
  printf("- Cada jogador podera somente jogar uma determinada peca se esta estiver disponivel em sua mao (excecao: modo CHEAT).\n\n");
  printf("- Uma jogada e valida se atender os seguintes requisitos:\n");
  printf(" > A peca jogada deve estar conectada (pela linha ou coluna) com outras pecas (excecao: primeira jogada);\n");
  printf(" > Nao ha, entre a sequencia de pecas que o ladrilho jogado toca, um ladrilho igual ja jogado;\n");
  printf(" > O formato (A, B, C, D, E ou F) do ladrilho ou sua cor (1, 2, 3, 4, 5 ou 6) devem ser os mesmos das sequencias de pecas que aparecem nas filas que passam pela posicao jogada;\n");
  printf(" > Nao pode haver espacos vazios entre dois ladrilhos jogados em uma mesma rodada;\n\n");
  printf("- O jogador so podera trocar pecas se ele nao tiver realizado nenhuma jogada na rodada.\n\n");
  printf("- E possivel trocar quantos ladrilhos desejar durante uma troca, mas e possivel realizar somente uma troca por rodada.\n\n");

  printf("\n%s 1 %s 2  3  4  5  6\n\n", BG_RED, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}

void printSegunPag(){

  limparTela();
  printLogo();

  printf("\nEXEMPLOS BASICOS:\n\n");

  Ladrilho l1, l2, l3;
  l1.tipo = 'A';
  l2.tipo = 'A';
  l3.tipo = 'A';
  l1.cor = 1;
  l2.cor = 3;
  l3.cor = 6;

  printf("- Exemplos de sequencias validas de ladrilhos: \n\n");
  printf("1 - ");
  printLadrilho(l1);
  //printf(" ");
  printLadrilho(l2);
  printLadrilho(l3);
  printf(" ou ");

  l1.tipo = 'A';
  l2.tipo = 'C';
  l3.tipo = 'F';
  l1.cor = 4;
  l2.cor = 4;
  l3.cor = 4;
  printLadrilho(l1);
  printLadrilho(l2);
  printLadrilho(l3);
  printf("\n\n");

  printf("2 - ");
  printLadrilho(l1);
  printf("    ");
  l1.tipo = 'A';
  l1.cor = 1;
  printLadrilho(l1);
  printf("\n    ");
  printLadrilho(l2);
  printf(" ou ");  
  l2.tipo = 'A';
  l2.cor = 3;
  printLadrilho(l2);
  printf("\n    ");  
  printLadrilho(l3);
  printf("    ");  
  l3.tipo = 'A';
  l3.cor = 6;
  printLadrilho(l3);

  printf("\n\n3 - ");
  printLadrilho(LADR_VAZIO());
  printLadrilho(l1);
  printf("\n    ");
  l1.tipo = 'B';
  l1.cor = 3;
  printLadrilho(l1);
  printLadrilho(l2);
  l1.tipo = 'C';
  l1.cor = 3;
  printLadrilho(l1);
  printf("\n    ");
  printLadrilho(LADR_VAZIO());
  printLadrilho(l3);

  printf("\n\n 1 %s 2 %s 3  4  5  6\n\n", BG_GREEN, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");
  
}

void printTercPag(){

  limparTela();
  printLogo();

  printf("\nCOMANDOS BASICOS:\n");
  printf("(Obs: Os comandos podem ser utilizados escrevendo somente a primeira letra do mesmo ou digitando o comando inteiro, nao importando letra minuscula ou maiscula. Ex: Novo = novo = NoVo = n = N\n\n");
  // jogar -> EM_JOGO
  // passar -> EM_JOGO
  // trocar -> EM_JOGO
  // sair -> EM_JOGO
  // novo -> JOGO_PARADO
  // fechar -> JOGO_PARADO

  printf("- NOVO, novo, n -> Inicia um novo jogo.\n");
  printf("- FECHAR, fechar, f -> Fechar a aplicacao.\n");
  printf("- jogar <peca> <linha> <coluna> -> Jogar um ladrilho. Exemplo: j A2 0 3\n");
  printf("- trocar <peca_1> ... <peca_n> -> Troca peca(s). Exemplo: t A1 B4\n");
  printf("- Passar, passar, p -> Passa a vez para o proximo jogador.\n");
  printf("- Sair, sair, s -> Sai da partida indicando o vencedor caso haja, ou os jogadores empatados.\n");

  printf("\n\n 1  2 %s 3 %s 4  5  6\n\n", BG_YELLOW, BG_END);
 
  
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}


void printQuarPag(){

limparTela();
printLogo();

printf("\nPONTUACAO:\n\n");
printf("- Cada ladrilho vale 1 ponto.\n\n");
printf("- Ao jogar um ladrilho, a pontuacao sera feita da seguinte maneira: serao contados quantos ladrilhos em sequencia existem tanto na linha quanto na coluna que passam pela posicao jogada, com a pontuacao final sendo igual a quantidade de ladrilhos contados. Observacao: Cada fila so podera ser contado uma vez por rodada.\n\n");
printf("- Caso uma sequencia de pecas tenha tamanho 6 temos um Qwirkle, que vale 12 pontos.\n\n");
printf("- Ao final, ganha quem fizer mais pontos, com a possibilidade de empate.\n\n");
printf("- Na proxima tela voce tera detalhes de quando o jogo acaba.\n\n");
printf("- Bom Jogo!\n");


  printf("\n\n 1  2  3 %s 4 %s 5  6\n\n",BG_BLUE , BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}
void printQuinPag(){

limparTela();
printLogo();

printf("\nFIM DE JOGO:\n\n");
printf("- Existem tres maneiras de se terminar um jogo:\n");
printf(" > Primeira: ao digitar o comando sair no meio da partida esta sera finalizada, contabilizando pontos e mostrando se ha ganhadores ou o jogo terminou em empate.\n");
printf("\n > Segunda: no momento em que nao houver mais ladrilhos disponiveis para comprar e um dos jogadores esgotar as pecas em sua mao, o jogo sera finalizado, com este ultimo jogador recebendo um bonus de 6 pontos. Por fim, as pontuacoes serao comparadas para se chegar no vencedor.\n");
printf("\n-ATENCAO-\n");

printf(" > A terceira maneira de acabar com o jogo eh tambem quando nao existem mais pecas para serem compradas, mas, nesse caso especifico, NENHUM jogador consegue realizar uma jogada valida. Caso isso aconteca, algum jogador deve chamar o comando sair, para que o jogo acabe e os pontos sejam computados e mostrando-se assim o vencedor ou os jogadores empatados.\n");


  printf("\n\n 1  2  3  4 %s 5 %s 6\n\n", BG_MAGENTA, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}
void printSexPag(){

  limparTela();
  printLogo();


  printf("\nMODO CHEAT: \n\n");
  printf("- O modo CHEAT eh um modo no qual nao existe a verificacao se a peca que o jogador deseja usar esta em sua mao ou nao. Em outras palavras, o jogador pode jogar qualquer ladrilho que desejar, desde que respeite todas as outras regras do jogo.\n");
  printf("- Alem disso todas as regras de pontuacao sao validas\n");
  printf("- Nao recomendamos a jogatina nele, sua real funcao consiste em testar se o esquema de pontuacao esta correto.\n");


  printf("\n\n 1  2  3  4  5 %s 6 %s\n\n", BG_CYAN, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}

int getCmd(){
  
  int n = 0;
  char cmd[20];
  
  fgets(cmd, 20, stdin);
  setbuf(stdin, NULL);

  if(cmd[0] == '1' && cmd[2] == '\0') n = 1;
  else if(cmd[0] == '2' && cmd[2] == '\0') n = 2;
  else if(cmd[0] == '3' && cmd[2] == '\0') n = 3;
  
  if(n == 1) proxPag();
  else if(n == 2) voltarPag();

  return n;
}

void gerenHelp(){

  int help = 1;

  while(help == 1){

    switch (pag){

      case 1:
        printPrimPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;

      case 2:
        printSegunPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;

      case 3:
        printTercPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;

      case 4:
        printQuarPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;  

      case 5:
        printQuinPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;

      case 6:
        printSexPag();
        if(getCmd() == 3){
          pag = 1;
          help = 0;
        }
        break;  

    }

  }

}

