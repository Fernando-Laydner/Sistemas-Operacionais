#include <stdio.h>
#include <stdlib.h>
#include "IO_API.h"


err_t es_le(es_t *es, int dispositivo, int *pvalor){
    if (es->IO == dispositivo){
        printf("Digite um numero:\n ->");
        scanf("%d", pvalor);
        return ERR_OK;
    }
    else if(dispositivo == 1)
        return ERR_ES_OP_INV;
    else
        return ERR_ES_DISP_INV;
}

err_t es_escreve(es_t *es, int dispositivo, int valor){
    if (es->IO == dispositivo){
        printf("Numero digitado: %d\n", valor);
        return ERR_OK;
    }
    else if(dispositivo == 0)
        return ERR_ES_OP_INV;
    else
        return ERR_ES_DISP_INV;
}

es_t *es_cria(){
    es_t *io;

    io = malloc(sizeof(es_t));
    io->IO = 0; // teclado

    return io;
}

void es_muda(es_t *es, int dispositivo){
    es->IO = dispositivo;
}

/*
int main(){

    es_t *es;

    es = es_cria(); // iniciado como teclado

    int teste;
    while(1){
        es_muda(es, 0);
        es_le(es, 0, &teste);
        es_muda(es, 1);
        es_escreve(es, 1, teste);
    }
}
*/
