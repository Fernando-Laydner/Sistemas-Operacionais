#include <stdio.h>
#include <stdlib.h>
#include "Memory_API.h"


int mem_tam(mem_t *m){
    return m->size;
}

void mem_escreve_tudo(mem_t *m){
    for (int i = 0; i < m->size; i++){
        printf("%d",m->memory[i]);
    }
    printf("\n");
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

/*
int main(){
    mem_t *memoria = mem_cria(5);

    mem_escreve_tudo(memoria);

    printf("size: %d\n", mem_tam(memoria));

    int i;
    mem_le(memoria, 1, &i);
    printf("i: %d\n", i);
    mem_escreve(memoria, 0, 10);
    mem_escreve(memoria, 1, 11);
    mem_escreve(memoria, 2, 12);
    mem_escreve(memoria, 3, 13);
    mem_escreve(memoria, 4, 14);
    mem_escreve_tudo(memoria);
    mem_le(memoria, 1, &i);
    printf("lendo i novo: %d", i);
    
}
*/
