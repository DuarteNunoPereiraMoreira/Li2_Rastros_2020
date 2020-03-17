//CAMADA DA INTERFACE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024
#include "interface.h"
#include "dados.h"
#include "logica.h"

void mostrar_tabuleiro(ESTADO *e)
{
    int linha, coluna, i;

    putchar('\n');
    printf("            a  b  c  d  e  f  g  h\n");
    printf("           __ __ __ __ __ __ __ __\n");

    for (linha = i = 7; linha >= 0; linha--, i--){
        printf("       %d  | ", i+1);
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 0 && linha == 0) printf("1  ");
            else if (coluna == 7 && linha == 7) printf("2  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == BRANCA) printf("*  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == PRETA) printf("#  ");
            else printf(".  ");
        }
        putchar('\n');
    }

    putchar('\n');
}


void mostrar_prompt(ESTADO *e){

    int jog_atual = obter_jogador_atual(e);
    int num_jogadas = obter_num_jogadas(e);

    printf("#(Jogada_%d) Player_%d faça a sua jogada> ", num_jogadas, jog_atual);
}


void mostrar_erro(ERROS erro){
    char *possiveis_erros[] = { "OK",
                                "Jogada inválida, tenta outra vez.",
                                "Coordenada inválida, tenta outra vez.",
                              };
    if (erro != OK) printf("%s\n\n\n", possiveis_erros[erro]);
}

void mostrar_vitoria(int jogador){
    printf("Parabéns Player%d, ganhou este jogo!!!\n", jogador);
}


int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int result;

    mostrar_tabuleiro(e);
    mostrar_prompt(e);

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        result = jogar(e, coord);
        putchar('\n');
        putchar('\n');
    }

    else if(strlen(linha) == 3 && sscanf(linha, "%[a-z]%[0-9]", col, lin) == 2)
        mostrar_erro(COORDENADA_INVALIDA);

    else printf("Este comando não é válido, tenta outra vez.\n\n\n");

    return result;
}