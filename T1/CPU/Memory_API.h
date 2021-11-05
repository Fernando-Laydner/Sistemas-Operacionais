#ifndef MEMORY_API_H
#define MEMORY_API_H

#include <stdio.h>
#include <stdlib.h>
#include "Erro.h"

typedef struct mem_t{
    int size;
    int memory[];
}mem_t;

int mem_tam(mem_t *m);

void mem_escreve_tudo(mem_t *m);

mem_t *mem_cria(int tam);

void mem_destroi(mem_t *m);

err_t mem_le(mem_t *m, int endereco, int *pvalor);

err_t mem_escreve(mem_t *m, int endereco, int valor);

#endif // MEMORY_API_H
