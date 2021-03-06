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
    int complemento;
    err_t modo;
}cpu_estado_t;

typedef struct cpu_t{
    cpu_estado_t *estado;
    mem_t *mem;
    es_t *es;
}cpu_t;

cpu_estado_t *cpu_estado(cpu_t *cpu);

void cpu_altera_estado(cpu_t *cpu, cpu_estado_t *estado);

void cpu_altera_memoria(cpu_t *cpu, mem_t *mem);

void cpu_altera_es(cpu_t *cpu, es_t *es);

cpu_estado_t *cpu_estado_cria();

void cpu_estado_destroi(cpu_estado_t *cpu_estado);

void cpu_estado_erro(cpu_estado_t *cpu_estado, err_t erro, int complemento);

cpu_t *cpu_cria();

void cpu_destroi(cpu_t *cpu);

err_t cpu_executa_1(cpu_t *cpu);

void imprime_estado(cpu_estado_t *estado);

#endif // CPU_API_H
