#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IO_API.h"
#include "CPU_API.h"
#include "Memory_API.h"
#include "CPU.h"



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
