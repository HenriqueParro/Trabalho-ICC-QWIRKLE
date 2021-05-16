#define TRUE    0
#define FALSE   1

#define SUCESSO               0
#define ERRO                  1
#define ERRO_MEMORIA         -1
#define ERRO_COORD_INVALIDA  -2
#define ERRO_COORD_OCUP      -3
#define ERRO_LADR_IGUAL      -4
#define ERRO_FILA_INV        -5
#define ERRO_CMD_INV         -6
#define ERRO_LADR_INDIS      -7 
#define ERRO_JOGADA_INVALIDA -8 
#define ERRO_LADR_ESGOTADOS  -9 
#define ERRO_LADR_INVALIDO   -10
#define ERRO_NUM_JOG_INV     -11 

int erro(int erro);
int getUltErro();
