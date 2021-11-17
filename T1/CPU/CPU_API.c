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
    cpu->estado = estado;
}

void cpu_altera_memoria(cpu_t *cpu, mem_t *mem){
    cpu->mem = mem;
}

void cpu_altera_es(cpu_t *cpu, es_t *es){
    cpu->es = es;
}

cpu_estado_t *cpu_estado_cria(){
    cpu_estado_t *temp = malloc(sizeof(cpu_estado_t));
    temp->modo = ERR_OK;
    temp->PC = 0;
    temp->A = 0;
    temp->X = 0;
    temp->complemento = 0;
    return temp;
}

void cpu_estado_destroi(cpu_estado_t *cpu_estado){
    free(cpu_estado);
}

void cpu_estado_erro(cpu_estado_t *cpu_estado, err_t erro, int complemento){
    cpu_estado->modo = erro;
    cpu_estado->complemento = complemento;
}

cpu_t *cpu_cria(){
    cpu_t *temp = malloc(sizeof(cpu_t));

    if (temp != NULL) {
        temp->estado = NULL;
        temp->mem = NULL;
        temp->es = NULL;
    }

    return temp;
}

void cpu_destroi(cpu_t *cpu){
  es_destroi(cpu->es);
  cpu_estado_destroi(cpu->estado);
  mem_destroi(cpu->mem);
  free(cpu);
}

err_t cpu_executa_1(cpu_t *cpu){

    int OP_Code;
    err_t erro = mem_le(cpu->mem, cpu_estado(cpu)->PC, &OP_Code);
    if (erro != ERR_OK){
        cpu_estado_erro(cpu_estado(cpu), erro, cpu_estado(cpu)->PC);
        return cpu_estado(cpu)->modo;
    }

    printf("\nOP_Code = %d\n", OP_Code);
    //printf("Mem antes:");
    //mem_escreve_tudo(cpu->mem);

    switch (OP_Code){
        case 0:
            NOP(cpu);
            break;
        case 1:
            PARA(cpu);
            break;
        case 2:
            CARGI(cpu);
            break;
        case 3:
            CARGM(cpu);
            break;
        case 4:
            CARGX(cpu);
            break;
        case 5:
            ARMM(cpu);
            break;
        case 6:
            ARMX(cpu);
            break;
        case 7:
            MVAX(cpu);
            break;
        case 8:
            MVXA(cpu);
            break;
        case 9:
            INCX(cpu);
            break;
        case 10:
            SOMA(cpu);
            break;
        case 11:
            SUB(cpu);
            break;
        case 12:
            MULT(cpu);
            break;
        case 13:
            DIV(cpu);
            break;
        case 14:
            RESTO(cpu);
            break;
        case 15:
            NEG(cpu);
            break;
        case 16:
            DESV(cpu);
            break;
        case 17:
            DESVZ(cpu);
            break;
        case 18:
            DESVNZ(cpu);
            break;
        case 19:
            LE(cpu);
            break;
        case 20:
            ESCR(cpu);
            break;
        default:
            cpu_estado_erro(cpu_estado(cpu), ERR_CPU_INSTR_INV, 0);
            break;
    }

    //printf("Mem dps:");
    //mem_escreve_tudo(cpu->mem);
    return cpu_estado(cpu)->modo;
}


void imprime_estado(cpu_estado_t *estado){
    printf( "\nPC: %d\nA: %d\nX: %d\nModo: %d", estado->PC, estado->A, estado->X, estado->modo);
}
