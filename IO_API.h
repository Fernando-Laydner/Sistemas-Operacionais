#ifndef IO_API_H
#define IO_API_H

#include <stdio.h>
#include <stdlib.h>
#include "Erro.h"

typedef struct es_t{
    int IO;
}es_t;

err_t es_le(es_t *es, int dispositivo, int *pvalor);

err_t es_escreve(es_t *es, int dispositivo, int valor);

es_t *es_cria();

void es_muda(es_t *es, int dispositivo);

#endif // IO_API_H