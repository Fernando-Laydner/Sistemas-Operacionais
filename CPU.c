#include <stdlib.h>
#include "CPU.h"
#include "CPU_API.h"
#include "Memory_API.h"
#include "IO_API.h"
#include "Erro.h"

err_t NOP(){
    return ERR_OK;
}

err_t PARA(){
    return ERR_CPU_PARADA;
}

err_t CARGI(cpu_t *cpu){
    return es_le(&cpu->es, 0, &cpu_estado(cpu)->A);
}

err_t CARGM(cpu_t *cpu){
    return mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &cpu_estado(cpu)->A);
}

err_t CARGX(cpu_t *cpu){
    return mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1 + cpu_estado(cpu)->X, &cpu_estado(cpu)->A);
}

err_t ARMM(cpu_t *cpu){
    return mem_escreve(&cpu->mem, cpu_estado(cpu)->PC + 1, cpu_estado(cpu)->A);
}

err_t ARMX(cpu_t *cpu){
    return mem_escreve(&cpu->mem, cpu_estado(cpu)->PC + 1 + cpu_estado(cpu)->X, cpu_estado(cpu)->A);
}

err_t MVAX(cpu_t *cpu){
    cpu_estado(cpu)->X = cpu_estado(cpu)->A;
    return ERR_OK;
}

err_t MVXA(cpu_t *cpu){
    cpu_estado(cpu)->A = cpu_estado(cpu)->X;
    return ERR_OK;
}

err_t INCX(cpu_t *cpu){
    cpu_estado(cpu)->X++;
    return ERR_OK;
}

err_t SOMA(cpu_t *cpu){
    int temp;
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &temp);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;
    cpu_estado(cpu)->A += temp;
    return ERR_OK;
}

err_t SUB(cpu_t *cpu){
    int temp;
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &temp);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;
    cpu_estado(cpu)->A -= temp;
    return ERR_OK;
}

err_t MULT(cpu_t *cpu){
    int temp;
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &temp);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;
    cpu_estado(cpu)->A *= temp;
    return ERR_OK;
}

err_t DIV(cpu_t *cpu){
    int temp;
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &temp);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;
    cpu_estado(cpu)->A /= temp;
    return ERR_OK;
}

err_t RESTO(cpu_t *cpu){
    int temp;
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &temp);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;
    cpu_estado(cpu)->A %= temp;
    return ERR_OK;
}

err_t NEG(cpu_t *cpu){
    cpu_estado(cpu)->A *= -1;
    return ERR_OK;
}

err_t DESV(cpu_t *cpu){
    return mem_le(&cpu->mem, cpu_estado(cpu)->PC + 1, &cpu_estado(cpu)->PC);
}

err_t DESVZ(cpu_t *cpu){
    if (cpu_estado(cpu)->A == 0){
        return DESV(cpu);
    }
    return ERR_OK;
}

err_t DESVNZ(cpu_t *cpu){
    if (cpu_estado(cpu)->A != 0){
        return DESV(cpu);
    }
    return ERR_OK;
}

err_t LE(cpu_t *cpu){
    return es_le(&cpu->es, 0, &cpu_estado(cpu)->A);
}

err_t ESCR(cpu_t *cpu){
    return es_escreve(&cpu->es, 1, cpu_estado(cpu)->A);
}