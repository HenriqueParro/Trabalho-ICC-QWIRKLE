#include <stdio.h>
#include <string.h>

#include "util.h"
#include "erros.h"

/*
* Calcula e retorna o valor de 'b' elevado a 'e', com 'e' inteiro e maior ou igual a zero. 
*/
int powInt(int b, int e){
    int r = 1;
    for(int i = 1; i <= e; i++) r *= b;
    return r;
}

/*
*   Converte o caracter que representa um numero em um tipo int.
*   Retorna o respectivo int se for um caracter valido, retorna -1 caso contrario.
*/
int convCharToInt(char c){

    switch (c) {

    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    
    default:
        return -1;
    }
}

/*
*   Funcao que le um numero pelo stdin.
*   Retorna ERRO caso seja um numero invalido, SUCESSO caso contrario.
*/
int lerIntSTDIN(int *n){

    char num[30];
    fgets(num, 30, stdin);
    num[strlen(num) - 1] = '\0';

    int m = (num[0] == '-') ? -1 : 1; 
    int i = (m == -1) ? 1 : 0;

    while(num[i] != '\0'){
        if(num[i] < '0' || num[i] > '9') return ERRO;
        i++;
    }

    int t = strlen(num);
    int inf = (m == -1) ? 1 : 0;

    (*n) = 0;
    for(int k = t - 1, j = 0; k >= inf; k--, j++) (*n) += convCharToInt(num[k])*powInt(10, j); 
    (*n) *= m;

    
       
    return SUCESSO;
}

/*
*   Funcao que compara duas strings sem distincao entre maiusculas e minusculas. 
*   Retorna TRUE se forem iguais, FALSE caso contrario.
*/
int cmpStr(char *str1, char *str2){

    int i = 0;
    while(str1[i] != '\0' || str2[i] != '\0'){

        if(str1[i] == str2[i]){
            i++;
            continue;
        } 

        if(str1[i] >= 'A' && str1[i] <= 'z' && str2[i] >= 'A' && str2[i] <= 'z'){
            if((str1[i] == str2[i] + 'a' - 'A') || (str2[i] == str1[i] + 'a' - 'A')){
                i++;
                continue;
            } 
        }

        return FALSE;
    }

    return TRUE;
}

