#include <stdio.h>
#include <stdlib.h>
#include "IO_API.h"


typedef enum { leitura, escrita } acesso_t;
typedef enum { teclado=0, video=1 } dispositivo_t;


static err_t verif_acesso(es_t *self, int dispositivo, acesso_t tipo){
  // só tem 2 dispositivos, teclado e video
  if (dispositivo != teclado && dispositivo != video) return ERR_ES_DISP_INV;
  // do teclado só dá para ler
  if (dispositivo == teclado && tipo != leitura) return ERR_ES_OP_INV;
  // o video é só para escrita
  if (dispositivo == video && tipo != escrita) return ERR_ES_OP_INV;

  return ERR_OK;
}

err_t es_le(es_t *es, int dispositivo, int *pvalor){
    err_t err = verif_acesso(es, dispositivo, leitura);
    if (err == ERR_OK) {
        printf("Digite um valor inteiro: ");
        scanf("%d", pvalor);
    }
    return err;
}

err_t es_escreve(es_t *es, int dispositivo, int valor){
    err_t err = verif_acesso(es, dispositivo, escrita);
    if (err == ERR_OK)
        printf("[%d]\n", valor);
  return err;
}

es_t *es_cria(){
    es_t *io;

    io = malloc(sizeof(es_t));

    return io;
}

void es_destroi(es_t *self){
  free(self);
}
