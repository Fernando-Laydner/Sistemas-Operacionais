#include <stdlib.h>

#include "CPU_API.h"
#include "CPU.h"
#include "Memory_API.h"
#include "IO_API.h"
#include "Erro.h"

// Funções complementares
err_t ARG(cpu_t *cpu, int pos, int *arg){
    err_t erro = mem_le(cpu->mem, cpu_estado(cpu)->PC + pos, arg);
    if (erro != ERR_OK){
        cpu_estado_erro(cpu_estado(cpu), erro, cpu_estado(cpu)->PC + pos);
        return cpu_estado(cpu)->modo;
    }
    printf("A1: %d\n", *arg);
    return cpu_estado(cpu)->modo;
}

void INCPC(cpu_t *cpu, int qnt){
    cpu_estado(cpu)->PC += qnt;
}

err_t DISP(cpu_t *cpu, int *dispositivo){
    return ARG(cpu, 1, dispositivo);
}


// Funções da CPU
void NOP(cpu_t *cpu){ // 0
    INCPC(cpu, 1);
}

void PARA(cpu_t *cpu){ // 1
    cpu_estado_erro(cpu_estado(cpu), ERR_CPU_PARADA, 0);
}

void CARGI(cpu_t *cpu){ // 2
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    cpu_estado(cpu)->A = A1;

    INCPC(cpu, 2);
}

void CARGM(cpu_t *cpu){ // 3
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    INCPC(cpu, 2);
}

void CARGX(cpu_t *cpu){ // 4
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1 + cpu_estado(cpu)->X);
        return;
    }

    INCPC(cpu, 2);
}

void ARMM(cpu_t *cpu){ // 5
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_escreve(cpu->mem, A1, cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    INCPC(cpu, 2);
}

void ARMX(cpu_t *cpu){ // 6
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_escreve(cpu->mem, A1 + cpu_estado(cpu)->X, cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1 + cpu_estado(cpu)->X);
        return;
    }

    INCPC(cpu, 2);
}

void MVAX(cpu_t *cpu){ // 7
    cpu_estado(cpu)->X = cpu_estado(cpu)->A;
    INCPC(cpu, 1);
}

void MVXA(cpu_t *cpu){ // 8
    cpu_estado(cpu)->A = cpu_estado(cpu)->X;
    INCPC(cpu, 1);
}

void INCX(cpu_t *cpu){ // 9
    cpu_estado(cpu)->X++;
    INCPC(cpu, 1);
}

void SOMA(cpu_t *cpu){ // 10
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &A1);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    cpu_estado(cpu)->A += A1;
    INCPC(cpu, 2);
}

void SUB(cpu_t *cpu){ // 11
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &A1);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    cpu_estado(cpu)->A -= A1;
    INCPC(cpu, 2);
}

void MULT(cpu_t *cpu){ // 12
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &A1);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    cpu_estado(cpu)->A *= A1;
    INCPC(cpu, 2);
}

void DIV(cpu_t *cpu){ // 13
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &A1);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    cpu_estado(cpu)->A /= A1;
    INCPC(cpu, 2);
}

void RESTO(cpu_t *cpu){ // 14
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    err_t erro = mem_le(cpu->mem, A1, &A1);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, A1);
        return;
    }

    cpu_estado(cpu)->A %= A1;
    INCPC(cpu, 2);
}

void NEG(cpu_t *cpu){ // 15
    cpu_estado(cpu)->A *= -1;
    INCPC(cpu, 1);
}

void DESV(cpu_t *cpu){ // 16
    int A1;
    if (ARG(cpu, 1, &A1))
        return;

    cpu_estado(cpu)->PC = A1;
}

void DESVZ(cpu_t *cpu){ // 17
    if (cpu_estado(cpu)->A == 0)
        return DESV(cpu);
    INCPC(cpu, 2);
}

void DESVNZ(cpu_t *cpu){ // 18
    if (cpu_estado(cpu)->A != 0)
        return DESV(cpu);
    INCPC(cpu, 2);
}

void LE(cpu_t *cpu){ // 19
    int dispositivo;
    if (DISP(cpu, &dispositivo))
        return;

    err_t erro = es_le(cpu->es, dispositivo, &cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, dispositivo);
        return;
    }

    INCPC(cpu, 2);
}

void ESCR(cpu_t *cpu){ // 20
    int dispositivo;
    if (DISP(cpu, &dispositivo))
        return;

    err_t erro = es_escreve(cpu->es, dispositivo, cpu_estado(cpu)->A);
    if (erro){
        cpu_estado_erro(cpu_estado(cpu), erro, dispositivo);
        return;
    }

    INCPC(cpu, 2);
}
