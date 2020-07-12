#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <ctype.h>

#include "util.h"
#include "interface.h"
#include "erros.h"
#include "gerenciador.h"
#include "jogador.h"
#include "help.h"

/*
* Esta funcao distribui os ladrilhos presentes no vetor de ladrilhos da struct Tabuleiro entre as maos dos jogadores. Apos isso, ela reeordena o vetor citado.
*/
void distLadr(Gerenciador *g){
  
  int cont = 0;
  for(int i = 0; i < g->qntJog; i++){
    for(int j = 0; j < LADR_MAO; j++, cont++){
      g->listJog[i].ladr[j] = g->tab.ladr[cont];
      g->listJog[i].ladrMao++;
      g->tab.ladr[cont] = LADR_VAZIO();
      g->tab.ladrDisp--;
    }
  }

  ordenarListLadr(g->tab.ladr, QNT_PECAS);
}

/*
* Funcao que inicializa todos os campos da struct Gerenciador, fazendo tambem toda alocacao de memoria necessaria.
*/
int iniciarGerenciador(Gerenciador *g){
  
  limparTela();
  printLogo();
  printErro();
  printf("Escolha o numero de jogadores (Min: 1 | Max: 18): ");

  int n;
  
  while (lerIntSTDIN(&n) == ERRO || n <= 0 || n > NUM_MAX){
    erro(ERRO_NUM_JOG_INV);
    limparTela();
    printLogo();
    printErro();
    printf("Escolha o numero de jogadores:");
    setbuf(stdin, NULL);  
  }

  erro(SUCESSO);

  g->listJog = (Jogador*) malloc(n*sizeof(Jogador)); 
  if(g->listJog == NULL) return erro(ERRO_MEMORIA);

  g->qntJog = n;
  g->jogDaVez = 0;
  g->coord[0] = -1;
  g->coord[1] = -1;
  g->fila = 'n';
  g->jogadasRodada = 0;
  g->primJogada = TRUE;
  g->primRodada = TRUE;
  
  for(int i = 0; i < n; i++){

    limparTela();
    printLogo();
    printErro();
    
    printf("Digite o nome do Jogador [%d]: ", i+1);
    fgets(g->listJog[i].nome, 16, stdin);
    g->listJog[i].nome[strlen(g->listJog[i].nome) - 1] = '\0';
    g->listJog[i].pontTotal = 0;
    g->listJog[i].ladrMao = 0;
  }

  do {

    limparTela();
    printLogo();
    printErro();

    printf("Modo CHEAT(S/N): ");
    char aux[10];
    fgets(aux, 10, stdin);
    g->cheat = aux[0];

    erro(ERRO_CMD_INV);

  } while(g->cheat != 's' && g->cheat != 'S' && g->cheat != 'n' && g->cheat != 'N');

  erro(SUCESSO);
  
  int e = iniciarTabuleiro(&g->tab);
  if(e != SUCESSO){
    free(g->listJog);
    return erro(e);
  }

  distLadr(g);
  g->estado = EM_JOGO;

  return erro(SUCESSO);
}

/*
* Funcao que libera a memoria alocada na funcao iniciarGerenciador();
*/
void encerrarGerenciador(Gerenciador *g){

  if(g->tab.matriz != NULL) liberarTabuleiro(&g->tab);
  if(g->listJog != NULL) free(g->listJog);
}

/*
* Funcao que verifica se um determinado ladrilho respeita o tipo (formato) dos outros ladrilhos de uma determina fila que passa pela posicao jogada.
*/
int verifTipoFila(Gerenciador *g, Ladrilho l, int x, int y, char fila, int *count){

  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);
  
  int acres = 1;
  
  if(fila == 'l'){

    //tipo na linha comecando na esquerda
    while(coluna - acres >= 0 && cmpLadr(g->tab.matriz[linha][coluna-acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna-acres].tipo == l.tipo){
        if (g->tab.matriz[linha][coluna-acres].cor == l.cor) return erro(ERRO_LADR_IGUAL);
      } else return FALSE; 
      acres++;
    }
    *count += acres;

    // tipo  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna + acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna + acres].tipo == l.tipo){
        if (g->tab.matriz[linha][coluna + acres].cor == l.cor) return erro(ERRO_LADR_IGUAL);
      } else return FALSE; 
      acres++; 
    }
    *count += acres;
    
  } else {
    
    //tipo na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna],LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha - acres][coluna].cor == l.cor) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;
      acres++;  
    }
    *count += acres;

    // tipo na linha pra baixo
    acres = 1;
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha + acres][coluna].cor == l.cor) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;
      acres++;
    }
    *count += acres;

  }

  return erro(SUCESSO);
}

/*
* Funcao que verifica se um determinado ladrilho respeita a cor dos outros ladrilhos de uma determina fila que passa pela posicao jogada.
*/
int verifCorFila(Gerenciador *g, Ladrilho l, int x, int y, char fila, int *count){
  
  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);
  
  int acres = 1;
  
  if(fila == 'l'){  

    //cor na linha comecando na esquerda
    while(coluna - acres >= 0 && cmpLadr(g->tab.matriz[linha][coluna-acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna-acres].cor == l.cor){
        if (g->tab.matriz[linha][coluna-acres].tipo == l.tipo) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;
      acres++;
    }
    *count += acres;

  // cor  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna+acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna+acres].cor == l.cor){
        if (g->tab.matriz[linha][coluna+acres].tipo == l.tipo) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;  
      acres++;  
    }
    *count += acres;    
  
  } else {

    //cor na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;
      acres++;
    }
    *count += acres;

    // cor na linha pra baixo
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo) return erro(ERRO_LADR_IGUAL);
      } else return FALSE;  
      acres++;
    }
    *count += acres;
    
  }

  return erro(SUCESSO);
}

/*
* Funcao que verifica se uma determinada jogada é valida ou não.
*/
int jogadaValida(Gerenciador *g, Ladrilho l, int x, int y){

  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);

  if(linha < 0 || linha >= DIM || coluna < 0 || coluna >= DIM) return erro(ERRO_COORD_INVALIDA);
  if(cmpLadr(g->tab.matriz[linha][coluna], LADR_VAZIO()) == FALSE) return erro(ERRO_COORD_OCUP);

  int i = 0;
  if(g->cheat != 'S' && g->cheat != 's'){
    for (i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
      if(cmpLadr(l, g->listJog[g->jogDaVez].ladr[i]) == TRUE) break;
    }
  }

  if(i >= g->listJog[g->jogDaVez].ladrMao) return erro(ERRO_LADR_INDIS);

  int count = 0;
  if(verifCorFila(g, l, x, y, 'l', &count) == SUCESSO){
    if(verifCorFila(g, l, x, y, 'c', &count) != SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c', &count) != SUCESSO) return erro(ERRO_JOGADA_INVALIDA);
    } else if(count == 4 && g->primJogada == FALSE) return erro(ERRO_JOGADA_INVALIDA);
  } else {
    if(verifTipoFila(g, l, x, y, 'l', &count) == SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c', &count) != SUCESSO){
        if(verifCorFila(g, l, x, y, 'c', &count) != SUCESSO) return erro(ERRO_JOGADA_INVALIDA);
      } else if(count == 4 && g->primJogada == FALSE) return erro(ERRO_JOGADA_INVALIDA);
    } else return erro(ERRO_JOGADA_INVALIDA);
  } 

  if(g->fila == 'n'){

    if(g->primJogada == FALSE){
      g->coord[0] = linha;
      g->coord[1] = coluna;
    } else {
      g->coord[0] = convCoordJogoMatriz(0);
      g->coord[1] = convCoordJogoMatriz(0);
      linha = convCoordJogoMatriz(0);
      coluna = convCoordJogoMatriz(0);
    }
      g->fila = 'a';  
      
  } else if(g->fila == 'a'){

    if(g->coord[0] == linha) g->fila = 'l';
    else if(g->coord[1] == coluna) g->fila = 'c';
    else return erro(ERRO_FILA_INV);

  } else if(g->fila == 'l'){
    if(g->coord[0] != linha) return erro(ERRO_FILA_INV);

  } else if(g->fila == 'c'){
    if(g->coord[1] != coluna) return erro(ERRO_FILA_INV);
  }

  if(linha == g->coord[0] && coluna != g->coord[1]){
    
    int sent;
    if(coluna > g->coord[1]) sent = 1; //verificar a direita
    else sent = -1; //verificar a esquerda
    
    int c = g->coord[1] + sent;
    while(c != coluna){
      if(cmpLadr(g->tab.matriz[linha][c], LADR_VAZIO()) == TRUE) return erro(ERRO_JOGADA_INVALIDA); 
      c += sent;
    }
  } else if(coluna == g->coord[1] && linha != g->coord[0]){

    int sent;
    if(linha > g->coord[0]) sent = 1; // verificar para baixo
    else sent = -1; // veficar para cima

    int l = g->coord[0] + sent;
    while(l != linha){
      if(cmpLadr(g->tab.matriz[l][coluna], LADR_VAZIO()) == TRUE) return erro(ERRO_JOGADA_INVALIDA);
      l += sent;
    }

  }

  if(g->cheat != 'S' && g->cheat != 's'){
    g->listJog[g->jogDaVez].ladr[i] = LADR_VAZIO();
    ordenarListLadr(g->listJog[g->jogDaVez].ladr, LADR_MAO);
    g->listJog[g->jogDaVez].ladrMao--;
  }

  return erro(SUCESSO);
}

/*
* Esta funcao realiza a jogada validada na funcao jogadaValida
*/
int jogarLadr(Gerenciador *g, Ladrilho ladrilho, int x, int y){
  
  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);

  int e = jogadaValida(g, ladrilho, x, y);
  if(e != SUCESSO) return erro(e);
  
  if(g->primJogada == TRUE){
    linha = convCoordJogoMatriz(0);
    coluna = convCoordJogoMatriz(0);
    x = 0;
    y = 0;
  }

  g->primJogada = FALSE;
  g->tab.matriz[linha][coluna] = ladrilho;

  if(g->fila == 'a'){

    for(int i = 0; i < 6; i++){
      g->ultJogadas[i][0] = 0;
      g->ultJogadas[i][1] = 0;
    }
      g->ultJogadas[0][0] = x;
      g->ultJogadas[0][1] = y;
      g->jogadasRodada = 1;

  } else {

    g->ultJogadas[g->jogadasRodada][0] = x;
    g->ultJogadas[g->jogadasRodada][1] = y;
    g->jogadasRodada++;
  }

  if(x <= g->tab.lSup) g->tab.lSup = x;
  if(x >= g->tab.lInf) g->tab.lInf = x;

  if(y <= g->tab.cEsq) g->tab.cEsq = y;
  if(y >= g->tab.cDir) g->tab.cDir = y;

  return erro(SUCESSO);
}

/*
* Esta funcao realiza a troca de ladrilhos entra a mao do jogador e os ladrilhos do tabuleiro.
*/
int trocarLadr(Gerenciador *g, Ladrilho l){

  if(g->tab.ladrDisp <= 0) return erro(ERRO_LADR_ESGOTADOS); 
  
  unsigned static int r;
  srand(time(NULL) + r);
  
  int i;
  for(i = 0; i < LADR_MAO; i++){
    if(cmpLadr(g->listJog[g->jogDaVez].ladr[i], l) == TRUE) break;
  }

  if(i == LADR_MAO) return erro(ERRO_LADR_INDIS);

  int j = rand() % g->tab.ladrDisp;
  Ladrilho aux = l;
  g->listJog[g->jogDaVez].ladr[i] = g->tab.ladr[j];
  g->tab.ladr[j] = aux;

  ordenarListLadr(g->tab.ladr, QNT_PECAS);
  r++;

  return erro(SUCESSO);
}

/*
* Esta funcao realiza a contagem de pontos de uma determinada fila que passa por um ponto dado.
*/
int pontuacaoFila(Gerenciador g, int x, int y, char fila){

  int pont = 0;

  int l = convCoordJogoMatriz(x);
  int c = convCoordJogoMatriz(y);

  if(fila == 'l'){ // verificacao em linha
    
    // verificacao em linha para a esquerda
    int acres = 1;
    while(cmpLadr(g.tab.matriz[l][c - acres], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    // verificacao em linha para a direita
    acres = 1;
    while(cmpLadr(g.tab.matriz[l][c + acres], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    if(pont != 0) pont++;
    
    if(pont == 6) return QWIRKLE;
    else return pont;
    
  } else { // verificacao em coluna
    
    // verificacao em coluna para baixo
    int acres = 1;
    while(cmpLadr(g.tab.matriz[l - acres][c], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    // verificacao em coluna para cima
    acres = 1;
    while(cmpLadr(g.tab.matriz[l + acres][c], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }
    
    if(pont != 0) pont++;

    if(pont == 6) return QWIRKLE;
    else return pont;
  }
}


/*
* Funcao que contabiliza a pontuacao de um jogador.
*/
void verifPont(Gerenciador *g){

  if(g->fila == 'a'){ // apenas 1 jogada

    int aux = g->listJog[g->jogDaVez].pontTotal;
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'l');
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'c');
    
    if(g->listJog[g->jogDaVez].pontTotal == aux) g->listJog[g->jogDaVez].pontTotal++;

  } else if(g->fila == 'l'){ 

    for(int i = 0; i < g->jogadasRodada; i++){
      printf("Pont[%d]: %d\n", i,  g->listJog[g->jogDaVez].pontTotal);
      printf("(%d, %d)\n", g->ultJogadas[i][0], g->ultJogadas[i][1]);
      g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[i][0], g->ultJogadas[i][1], 'c');
    }
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'l');

  } else if(g->fila == 'c'){

    for(int i = 0; i < g->jogadasRodada; i++){
      g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[i][0], g->ultJogadas[i][1], 'l');
    }
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'c');
  }
}

/*
* Funcao que passa pela pontucao de cada jogador e verifica quem é o vencedor em caso de vitoria ou quem sao os empatados em caso de empate, em ambos os casos ela mostra a pontuacao.
*/
int verifGanhador(Gerenciador *g){
  
  if(g->tab.ladrDisp <= 0 ){
    for(int i = 0; i < g->qntJog; i++){
      if(g->listJog[i].ladrMao <= 0){

        g->listJog[i].pontTotal += 6;
        verifPont(g);

        Jogador aux;
        aux.pontTotal = -1;

        int qnt_vencedores = 1;
        int id_vencedores[g->qntJog];
        for(int i = 0; i < g->qntJog; i++){

          if(g->listJog[i].pontTotal > aux.pontTotal){
            aux = g->listJog[i];
            qnt_vencedores = 1;
            id_vencedores[qnt_vencedores - 1] = i;

          } else if(g->listJog[i].pontTotal == aux.pontTotal){
            qnt_vencedores++;
            id_vencedores[qnt_vencedores - 1] = i;    
          } 
      }

      limparTela();
      printLogo();
      printTabuleiro(g->tab);

      if(qnt_vencedores == 1){
        printf("Ganhador: \n\n%s %s %s (Pontuacao Total: %d)\n", BG_BLUE, aux.nome, BG_END, aux.pontTotal);
      } else {
        printf("Empate: \n\n");
        for(int i = 0; i < qnt_vencedores; i++){
          aux = g->listJog[id_vencedores[i]];
          printf("%s %s %s (Pontuacao Total: %d)\n", BG_BLUE, aux.nome, BG_END, aux.pontTotal);
        }     
      }

      g->estado = JOGO_PARADO;
      printf("\n\nPressione ENTER para continuar\n");
    
      char exit[20];
      fgets(exit, 20, stdin);

      return TRUE;
    } 
  }

  return FALSE;

  } else return FALSE;
}

/*
* Funcao para captar os comandos do usuario: jogar, passar, trocar, sair
*/
void escolherComando(Gerenciador *g){

  fseek(stdin, 0, SEEK_END);

  int retorno;
  erro(SUCESSO);
  
  char cmd[100];
  fgets(cmd, 100, stdin);
  cmd[strlen(cmd) - 1] = '\0';

  char *token = NULL;
  token = strtok(cmd, " ");

  if(token == NULL){
    erro(ERRO_CMD_INV);
    return;
  }

  /* ---- Setor do comando JOGAR ---- */
  if(cmpStr(token, "jogar") == TRUE || cmpStr(token, "j") == TRUE){

    if(g->estado != EM_JOGO){
      erro(ERRO_CMD_INV);
      return;
    }
    
    token = strtok(NULL, " ");

    if(token == NULL){
      erro(ERRO_CMD_INV);
      return;
    }

    if(strlen(token) != 2){
      erro(ERRO_LADR_INVALIDO);
      return;
    }

    if((token[0] < 'A' || token[0] > 'F') && (token[0] < 'a' || token[0] > 'f')){
      erro(ERRO_LADR_INVALIDO);
      return;
    } 
    
    if(token[1] < '0' || token[1] > '9'){
      erro(ERRO_LADR_INVALIDO);
      return;
    }

    Ladrilho l; 
    token[0] = toupper(token[0]);
    l.tipo = token[0]; 
    l.cor = atoi(&token[1]);

    token = strtok(NULL, " ");

    if(token == NULL){
      erro(ERRO_CMD_INV);
      return;
    }
    
    for(int i = 0; token[i] != '\0'; i++){ 
      if(token[0] == '-' && i == 0) continue;
      if(token[i] < '0' || token[i] > '9'){
        erro(ERRO_COORD_INVALIDA);
        return;
      }
    }

    if(strlen(token) == 1 && token[0] == '-') return;
    int x = atoi(token);

    token = strtok(NULL, " ");
    if(token == NULL){
      erro(ERRO_CMD_INV);
      return;
    }
    
    for(int i = 0; token[i] != '\0'; i++){
      if(token[0] == '-' && i == 0) continue;
      if(token[i] < '0' || token[i] > '9'){
        erro(ERRO_COORD_INVALIDA);
        return;       
      }
    }

    if(strlen(token) == 1 && token[0] == '-') return;
    int y = atoi(token);
    
    retorno = jogarLadr(g, l, x, y);
    if(retorno != SUCESSO){
      erro(retorno);
      return;
    }

    verifGanhador(g);

  /* ---- Fim do setor do comando JOGAR ---- */
    

  /* ---- Setor do comando PASSAR ---- */
  } else if(cmpStr(token, "passar") == TRUE || cmpStr(token, "p") == TRUE){
    
    if(g->estado != EM_JOGO){
      erro(ERRO_CMD_INV);
      return;
    }

    verifPont(g);

    g->fila = 'n';
    g->coord[0] = -1;
    g->coord[1] = -1;

    if(g->tab.ladrDisp > 0 && g->listJog[g->jogDaVez].ladrMao < LADR_MAO){
      
      int lm = g->listJog[g->jogDaVez].ladrMao;
      for(int i = 0; i < LADR_MAO - lm && g->tab.ladrDisp > 0; i++){
        trocarLadr(g, LADR_VAZIO());
        g->tab.ladrDisp--;
        g->listJog[g->jogDaVez].ladrMao++;
      }
    }

    g->primRodada = FALSE;
    g->jogDaVez++;
    if(g->jogDaVez >= g->qntJog) g->jogDaVez = 0; 

  /* ---- Fim do setor do comando PASSAR ---- */
  
  /* ---- Setor do comando TROCAR ---- */
  } else if(cmpStr(token, "trocar") == TRUE || cmpStr(token, "t") == TRUE){
    
    if(g->estado != EM_JOGO){
      erro(ERRO_CMD_INV);
      return;
    }

    if(g->listJog[g->jogDaVez].ladrMao < 6){
      erro(ERRO_CMD_INV);
      return;
    }

    int qntLadr = 0;
    Ladrilho ladrCMD[6];
    token = strtok(NULL, " ");
    
    do {
      
      if(token == NULL){
        erro(ERRO_CMD_INV);
        return;
      }

      if(strlen(token) != 2){
        erro(ERRO_LADR_INVALIDO);
        return;
      }

      if((token[0] < 'A' || token[0] > 'F') && (token[0] < 'a' || token[0] > 'f')){
        erro(ERRO_LADR_INVALIDO);
        return;
      } 
    
      if(token[1] < '0' || token[1] > '9'){
        erro(ERRO_LADR_INVALIDO);
        return;
      }

      Ladrilho l;
      token[0] = toupper(token[0]);
      l.tipo = token[0];
      l.cor = atoi(&token[1]);

      ladrCMD[qntLadr] = l;
      qntLadr++;

      token = strtok(NULL, " ");

    } while (token != NULL && qntLadr < 6);

    Ladrilho aux[6];
    for(int i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
      aux[i] = g->listJog[g->jogDaVez].ladr[i];
    }

    for(int i = 0; i < qntLadr; i++){
      if(trocarLadr(g, ladrCMD[i]) != SUCESSO){
        for(int j = 0; j < g->listJog[g->jogDaVez].ladrMao; j++){
          g->listJog[g->jogDaVez].ladr[j] = aux[j];
        }
        return;
      }
    }

    g->primRodada = FALSE;
    g->jogDaVez++;
    if(g->jogDaVez >= g->qntJog) g->jogDaVez = 0;
    
  /* ---- Fim do setor do comando TROCAR ---- */
  
  /* ---- Setor do comando SAIR ---- */
  } else if(cmpStr(token, "sair") == TRUE || cmpStr(token, "s") == TRUE){
    
    if(g->estado != EM_JOGO){
      erro(ERRO_CMD_INV);
      return;
    }

    verifPont(g);

    Jogador aux;
    aux.pontTotal = -1;

    int qnt_vencedores = 1;
    int id_vencedores[g->qntJog];
    for(int i = 0; i < g->qntJog; i++){

      if(g->listJog[i].pontTotal > aux.pontTotal){
        aux = g->listJog[i];
        qnt_vencedores = 1;
        id_vencedores[qnt_vencedores - 1] = i;

      } else if(g->listJog[i].pontTotal == aux.pontTotal){
        qnt_vencedores++;
        id_vencedores[qnt_vencedores - 1] = i;    
      }    
    }
    g->estado = JOGO_PARADO;

    limparTela();
    printLogo();
    printTabuleiro(g->tab);

    if(qnt_vencedores == 1){
        printf("Ganhador: \n\n%s %s %s (Pontuacao Total: %d)\n", BG_BLUE, aux.nome, BG_END, aux.pontTotal);
    } else {
        printf("Empate: \n\n");
        for(int i = 0; i < qnt_vencedores; i++){
          aux = g->listJog[id_vencedores[i]];
          printf("%s %s %s (Pontuacao Total: %d)\n", BG_BLUE, aux.nome, BG_END, aux.pontTotal);
      }     
    }

    printf("\nPressione ENTER para continuar\n");
    
    char exit[20];
    fgets(exit, 20, stdin);

  /* ---- Fim do setor do comando SAIR ---- */

  /* ---- Setor do comando FECHAR ---- */
  } else if(cmpStr(token, "fechar") == TRUE || cmpStr(token, "f") == TRUE){

    if(g->estado != JOGO_PARADO){
      erro(ERRO_CMD_INV);
      return;
    }

    g->estado = EXIT;

  /* ---- Fim do setor do comando FECHAR ---- */

  /* ---- Setor do comando NOVO ---- */
  } else if(cmpStr(token, "novo") == TRUE || cmpStr(token, "n") == TRUE){

    if(g->estado != JOGO_PARADO){
      erro(ERRO_CMD_INV);
      return;
    }

    encerrarGerenciador(g);
    retorno = iniciarGerenciador(g);
    if(retorno != SUCESSO){
      erro(retorno);
      return;
    }

    g->estado = EM_JOGO;

  /* ---- Fim do setor do comando NOVO ---- */

  /* ---- Setor do comando HELP ---- */
  } else if(cmpStr(token, "help") == TRUE || cmpStr(token, "h") == TRUE){
      gerenHelp();
  /* ---- Fim do setor do comando HELP ---- */    
  }
  
  else {

    erro(ERRO_CMD_INV);
    return;
  }
}