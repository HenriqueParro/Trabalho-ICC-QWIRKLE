#include <stdio.h>

#include "interface.h"
#include "erros.h"

void limparTela(){
  printf("\e[H\e[2J");
}

void printLogo(){
  printf("\n");
  printf("  %s     %s   %s  %s      %s  %s  %s     %s  %s      %s   %s  %s  %s  %s  %s  %s       %s       %s\n", BG_RED, BG_END, BG_GREEN, BG_END,BG_GREEN, BG_END, BG_YELLOW, BG_END, BG_BLUE, BG_END, BG_MAGENTA, BG_END, BG_MAGENTA, BG_END, BG_CYAN, BG_END, BG_RED, BG_END);

  printf(" %s  %s   %s  %s  %s  %s      %s  %s   %s   %s   %s  %s   %s  %s  %s  %s %s  %s   %s  %s       %s  %s\n", BG_RED, BG_END, BG_RED, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_YELLOW, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END, BG_MAGENTA, BG_END, BG_MAGENTA, BG_END, BG_CYAN, BG_END, BG_RED, BG_END); 

  printf(" %s  %s   %s  %s  %s  %s   %s %s  %s  %s   %s   %s   %s      %s   %s    %s    %s  %s       %s     %s\n", BG_RED, BG_END, BG_RED, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_YELLOW, BG_END, BG_BLUE, BG_END, BG_MAGENTA, BG_END, BG_CYAN, BG_END, BG_RED, BG_END); 

  printf(" %s  %s  %s  %s   %s  %s %s   %s %s  %s    %s   %s   %s  %s  %s  %s   %s  %s %s  %s   %s  %s       %s  %s\n", BG_RED, BG_END, BG_RED, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_YELLOW, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END, BG_MAGENTA, BG_END, BG_MAGENTA, BG_END, BG_CYAN, BG_END, BG_RED, BG_END);

  printf("  %s    %s %s %s   %s  %s   %s  %s    %s     %s  %s  %s   %s  %s  %s  %s  %s  %s  %s       %s  %s       %s\n", BG_RED, BG_END, BG_RED, BG_END, BG_GREEN, BG_END, BG_GREEN, BG_END, BG_YELLOW, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END, BG_MAGENTA, BG_END, BG_MAGENTA, BG_END, BG_CYAN, BG_END, BG_RED, BG_END);
  printf("\n");
}

void printErro(){

  switch(getUltErro()){

    case SUCESSO:
      break;

    case ERRO_MEMORIA: 
      printf("%s ERROR DETECTED: %s Memory error.\n", BG_RED, BG_END);
      break;

    case ERRO_COORD_INVALIDA: 
      printf("%s ATTENTION: %s This position doesn't exist.\n", BG_RED, BG_END);
      break;

    case ERRO_COORD_OCUP:
      printf("%s ATTENTION: %s This position is occupied.\n", BG_RED, BG_END);
      break;

    case ERRO_LADR_IGUAL:
      printf("%s ATTENTION: %s This tile has already been used in that queue!\n", BG_RED, BG_END);
      break;
    
    case ERRO_FILA_INV:
      printf("%s ATTENTION: %s Invalid queue!\n", BG_RED, BG_END);
      break;

    case ERRO_CMD_INV:
      printf("%s ATTENTION: %s Invalid command!\n", BG_RED, BG_END);
      break;

    case ERRO_LADR_INDIS:
      printf("%s ATTENTION: %s Tile not available!\n", BG_RED, BG_END);
      break;
    
    case ERRO_JOGADA_INVALIDA:
      printf("%s ATTENTION: %s Invalid play!\n", BG_RED, BG_END);
      break;
     
    case ERRO_LADR_ESGOTADOS:   
      printf("%s ATTENTION: %s There are no more tiles avaliable for exchange!\n", BG_RED, BG_END);
      break;
      
    case ERRO_LADR_INVALIDO:
      printf("%s ATTENTION: %s Invalid tile!\n", BG_RED, BG_END);
      break;

    case ERRO_NUM_JOG_INV:
      printf("%s ATTENTION: %s Invalid number of players! (Min: 1 | Max: 18)\n", BG_RED, BG_END);
      break;
      
    default:
      printf("%s ERROR DETECTED: %s An unexpected error has occurred!\n", BG_RED, BG_END);
      break;
  }
}

void printLadrilho(Ladrilho lad){
  
  switch (lad.cor){

    case RED: 
      printf("%s %c%d \033[0m", BG_RED, lad.tipo, lad.cor);
      break;
      
    case GREEN: 
      printf("%s %c%d \033[0m", BG_GREEN, lad.tipo, lad.cor);
      break;

    case YELLOW: 
      printf("%s %c%d \033[0m", BG_YELLOW, lad.tipo, lad.cor);
      break;
    
    case BLUE: 
      printf("%s %c%d \033[0m", BG_BLUE, lad.tipo, lad.cor);
      break;

    case MAGENTA: 
      printf("%s %c%d \033[0m", BG_MAGENTA, lad.tipo, lad.cor);
      break;

    case CYAN:
      printf("%s %c%d \033[0m", BG_CYAN, lad.tipo, lad.cor);
      break;
    
    case GRAY:    
      printf("%s %c%d \033[0m", BG_GRAY, lad.tipo, lad.cor);
      break;

    default:
      printf("    ");
      break;
  }

}

/*
*   Funcao que printa o tabuleiro inteiro na tela.
*/
void printTabuleiro(Tabuleiro tab){

    //printar as coordenadas das colunas
    if(tab.cEsq <= -10) printf("     ");
    else printf("    ");
    for(int i = tab.cEsq - 1; i <= tab.cDir + 1; i++){

        if(i < 0){
            if(i <= -10) printf("  %d", i);
            else printf("   %d", i);
        } else {
            if(i <= 10) printf("    %d", i);
            else printf("   %d", i);
        }
    }

    printf("\n");

    //printar as linhas
    for(int i = tab.lSup - 1; i <= tab.lInf + 1; i++){
        
        printf("\n");

        if(i < 0){
            if(i <= -10) printf("%d   |    |", i);
            else printf(" %d   |    |", i);
        } else{
            if(i <= 9) printf("  %d   |    |", i);
            else printf(" %d   |    |", i);
        }

        if(i == tab.lSup - 1 || i == tab.lInf + 1){

            for(int j = tab.cEsq; j <= tab.cDir; j++) printf("    |");
            if(i < 0) printf("    |  %d", i);
            else printf("    |   %d", i);

        } else {

            for(int j = tab.cEsq; j <= tab.cDir; j++){
                printLadrilho(tab.matriz[convCoordJogoMatriz(i)][convCoordJogoMatriz(j)]);
                printf("|");
            } 
               
            if(i < 0) printf("    |  %d", i);
            else printf("    |   %d", i);

        }

        printf("\n");

        if(i < tab.lInf + 1){
            printf("      ");
            int qnt = 5*((tab.cDir + 1) - (tab.cEsq - 1) + 1) + 1;
            for(int k = 0; k < qnt; k++) printf("-");
        }
    }

    printf("\n");

    //printar as coordenadas das colunas
    if(tab.cEsq <= -10) printf("     ");
    else printf("    ");
    for(int i = tab.cEsq - 1; i <= tab.cDir + 1; i++){

        if(i < 0){
            if(i <= -10) printf("  %d", i);
            else printf("   %d", i);
        } else {
            if(i <= 10) printf("    %d", i);
            else printf("   %d", i);
        }
    }

    printf("\n\n");
}

/*
*   Funcao printa todos os ladrilhos que estao na mao do jogador.
*/
void printPecasJogador(Jogador jog){

    printf("| ");
    for(int i = 0; i < jog.ladrMao; i++){
        printLadrilho(jog.ladr[i]);
        printf(" | ");
    }
}

void printJogo(Gerenciador g){

    limparTela();
    
    printf("\n");
    if(g.primRodada == FALSE){
      
      if(g.cheat == 's' || g.cheat == 'S') printf("CHEAT MODE: %s ON %s   |   ", BG_GREEN, BG_END);
      
      if(g.jogDaVez == 0){
        printf("Previous round: Player [%s] (Score: %d)\n", g.listJog[g.qntJog - 1].nome, g.listJog[g.qntJog - 1].pontTotal);
      } else {
        printf("Previous round: Player [%s] (Score: %d)\n", g.listJog[g.jogDaVez - 1].nome, g.listJog[g.jogDaVez - 1].pontTotal);
      }

    } else {
      if(g.cheat == 's' || g.cheat == 'S') printf("Modo CHEAT: %s ON %s\n", BG_GREEN, BG_END);
      
    }

    printf("\n");
    printTabuleiro(g.tab);
    printf("\n");

    printf("Available commands: %s Play %s <tile> <row> <column> | %s Exchange %s <tile_1> ... <tile_n> | %s Pass %s | %s Quit %s | %s Help %s |\n\n", BG_BLUE, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END, BG_BLUE, BG_END);
    
    printf("Available tiles: ");
    printPecasJogador(g.listJog[g.jogDaVez]);
    printf("\n\n");
    
    printErro();
    printf("Player [%s] (Score: %d): ", g.listJog[g.jogDaVez].nome, g.listJog[g.jogDaVez].pontTotal);
}

void printPreJogo(Gerenciador g){

  limparTela();
  printLogo();

  printf("\n");
  printf("Available commands: %s New %s | %s Close %s | %s Help %s \n", BG_BLUE, BG_END, BG_BLUE,BG_END,BG_BLUE ,BG_END);
  printErro();
  printf("Enter a command: ");
}
