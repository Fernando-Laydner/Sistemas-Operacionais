#include <stdio.h>
#include <stdlib.h>
#include "Memory_API.h"


int mem_tam(mem_t *m){
    return m->size;
}

void mem_escreve_tudo(mem_t *mem){
    printf("[");
    for (int i = 0; i < mem->size - 1; i++){
        if (i != 0){
            printf(",");
        }
        printf(" %d", mem->memory[i]);
    }
    printf("]\n");
}

mem_t *mem_cria(int tam){
    mem_t *memoria;
    memoria = malloc(sizeof(mem_t) + (tam-1)*sizeof(int));
    memoria->size = tam;
    for (int i = 0; i< tam; i++){
        memoria->memory[i] = 0;
    }
    return memoria;
}

void mem_destroi(mem_t *m){
    free(m);
}

err_t mem_le(mem_t *m, int endereco, int *pvalor){
    if (endereco < m->size){
        *pvalor = m->memory[endereco];
        return ERR_OK;
    }
    return ERR_MEM_END_INV;

}

err_t mem_escreve(mem_t *m, int endereco, int valor){
    if (endereco < m->size){
        m->memory[endereco] = valor;
        return ERR_OK;
    }
    return ERR_MEM_END_INV;

}
