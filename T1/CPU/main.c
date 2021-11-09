#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IO_API.h"
#include "CPU_API.h"
#include "Memory_API.h"
#include "CPU.h"

#define TAM 20 // o tamanho da memória

cpu_estado_t *cpu_estado(cpu_t *cpu){
    cpu_estado_t *test;
    test = cpu->estado;
    return test;
}

void cpu_altera_estado(cpu_t *cpu, cpu_estado_t *estado){
    // só isso?
    cpu->estado = estado;
}

void cpu_altera_memoria(cpu_t *cpu, mem_t *mem){
    //cpu->mem = cpu_cria();
    cpu->mem = mem;
}

void cpu_altera_es(cpu_t *cpu, es_t *es){
    // só isso?
    cpu->es = es;
}

cpu_estado_t *cpu_estado_cria(){
    cpu_estado_t *temp = malloc(sizeof(cpu_estado_t));
    temp->modo = ERR_OK;
    temp->PC = 0;
    temp->A = 0;
    temp->X = 0;
    return temp;
}

cpu_t *cpu_cria(){
    cpu_t *temp = malloc(sizeof(cpu_t));
    return temp;
}

err_t cpu_executa_1(cpu_t *cpu){

    int A1;
    cpu_estado(cpu)->modo = mem_le(cpu->mem, cpu_estado(cpu)->PC, &A1);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;

    //printf("\nA1 = %d\n", A1);
    //printf("Mem antes:");
    //mem_escreve_tudo(cpu->mem);

    switch (A1){
        case 0:
            cpu_estado(cpu)->modo = NOP();
            break;
        case 1:
            cpu_estado(cpu)->modo = PARA();
            break;
        case 2:
            cpu_estado(cpu)->modo = CARGI(cpu);
            break;
        case 3:
            cpu_estado(cpu)->modo = CARGM(cpu);
            break;
        case 4:
            cpu_estado(cpu)->modo = CARGX(cpu);
            break;
        case 5:
            cpu_estado(cpu)->modo = ARMM(cpu);
            break;
        case 6:
            cpu_estado(cpu)->modo = ARMX(cpu);
            break;
        case 7:
            cpu_estado(cpu)->modo = MVAX(cpu);
            break;
        case 8:
            cpu_estado(cpu)->modo = MVXA(cpu);
            break;
        case 9:
            cpu_estado(cpu)->modo = INCX(cpu);
            break;
        case 10:
            cpu_estado(cpu)->modo = SOMA(cpu);
            break;
        case 11:
            cpu_estado(cpu)->modo = SUB(cpu);
            break;
        case 12:
            cpu_estado(cpu)->modo = MULT(cpu);
            break;
        case 13:
            cpu_estado(cpu)->modo = DIV(cpu);
            break;
        case 14:
            cpu_estado(cpu)->modo = RESTO(cpu);
            break;
        case 15:
            cpu_estado(cpu)->modo = NEG(cpu);
            break;
        case 16:
            cpu_estado(cpu)->modo = DESV(cpu);
            break;
        case 17:
            cpu_estado(cpu)->modo = DESVZ(cpu);
            break;
        case 18:
            cpu_estado(cpu)->modo = DESVNZ(cpu);
            break;
        case 19:
            cpu_estado(cpu)->modo = LE(cpu);
            break;
        case 20:
            cpu_estado(cpu)->modo = ESCR(cpu);
            break;
        default:
            cpu_estado(cpu)->modo = ERR_CPU_INSTR_INV;
            break;
    }
    /*
    if (){
        cpu_estado(cpu)->PC += 1;

    }
    */

    if (cpu_estado(cpu)->modo == ERR_OK && !(A1 == 16 || A1 == 17 || A1 == 18))
        cpu_estado(cpu)->PC += 1;

    //printf("Mem dps:");
    //mem_escreve_tudo(cpu->mem);
    return cpu_estado(cpu)->modo;
}

void imprime_estado(cpu_estado_t *estado){
    printf( "\nPC: %d\nA: %d\nX: %d\nModo: %d", estado->PC, estado->A, estado->X, estado->modo);
}

int main(){
    // programa para executar na nossa CPU
    int progr[TAM] = { 2, 0, 7, 2, 10, 5, 17,    //  0      x=0; l=10
                         8, 20, 1,                 //  7 ali: print x
                         9, 8, 11, 17, 18, 7,      // 10      if ++x != l goto ali
                         1,                        // 16      FIM
                         0                         // 17 aqui tá o "l"
                       };

    // variáveis que representam o computador
    mem_t *mem = mem_cria(TAM);
    es_t *es = es_cria();
    cpu_t *cpu = cpu_cria();
    cpu_estado_t *estado = cpu_estado_cria();

    // copia o programa para a memória
    for (int i = 0; i < TAM; i++) {
        if (mem_escreve(mem, i, progr[i]) != ERR_OK) {
            printf("Erro de memoria, endereco %d\n", i);
            exit(1);
        }
    }

    // inicializa a CPU com as variáveis criadas
    cpu_altera_estado(cpu, estado);
    cpu_altera_memoria(cpu, mem);
    cpu_altera_es(cpu, es);

    // executa uma instrução por vez até parar
    while (true) {
        //imprime_estado(cpu_estado(cpu));
        err_t err = cpu_executa_1(cpu);
        if (err != ERR_OK) {
            printf("Erro na execução: %d\n", err);
            printf("Estado final:\n");
            //imprime_estado(cpu_estado(cpu));
            break;
        }
    }

    // destroi todo mundo!
    return 0;
}
