#ifndef CPU_API_H
#define CPU_API_H

#include <stdio.h>
#include <stdlib.h>
#include "Memory_API.h"
#include "IO_API.h"

typedef struct cpu_estado_t{
    int PC;
    int A;
    int X;
    err_t modo;
}cpu_estado_t;

typedef struct cpu_t{
    cpu_estado_t *estado;
    mem_t *mem;
    es_t *es;
}cpu_t;

cpu_estado_t *cpu_estado(cpu_t *cpu);

cpu_estado_t *cpu_estado_cria();

cpu_t *cpu_cria();

void cpu_altera_estado(cpu_t *cpu, cpu_estado_t *estado);

void cpu_altera_memoria(cpu_t *cpu, mem_t *mem);

void cpu_altera_es(cpu_t *cpu, es_t *es);

err_t cpu_executa_1(cpu_t *cpu);

err_t NOP();

err_t PARA();

err_t CARGI(cpu_t *cpu);

err_t CARGM(cpu_t *cpu);

err_t CARGX(cpu_t *cpu);

err_t ARMM(cpu_t *cpu);

err_t ARMX(cpu_t *cpu);

err_t MVAX(cpu_t *cpu);

err_t MVXA(cpu_t *cpu);

err_t INCX(cpu_t *cpu);

err_t SOMA(cpu_t *cpu);

err_t SUB(cpu_t *cpu);

err_t MULT(cpu_t *cpu);

err_t DIV(cpu_t *cpu);

err_t RESTO(cpu_t *cpu);

err_t NEG(cpu_t *cpu);

err_t DESV(cpu_t *cpu);

err_t DESVZ(cpu_t *cpu);

err_t DESVNZ(cpu_t *cpu);

err_t LE(cpu_t *cpu);

err_t ESCR(cpu_t *cpu);

#endif // CPU_API_H
