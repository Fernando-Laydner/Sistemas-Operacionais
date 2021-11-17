#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include "CPU_API.h"
#include "Erro.h"
#include "Memory_API.h"
#include "IO_API.h"



err_t ARG(cpu_t *cpu, int pos, int *arg);

void INCPC(cpu_t *cpu, int qnt);

err_t DISP(cpu_t *cpu, int *dispositivo);

//////////

void NOP(cpu_t *cpu);

void PARA(cpu_t *cpu);

void CARGI(cpu_t *cpu);

void CARGM(cpu_t *cpu);

void CARGX(cpu_t *cpu);

void ARMM(cpu_t *cpu);

void ARMX(cpu_t *cpu);

void MVAX(cpu_t *cpu);

void MVXA(cpu_t *cpu);

void INCX(cpu_t *cpu);

void SOMA(cpu_t *cpu);

void SUB(cpu_t *cpu);

void MULT(cpu_t *cpu);

void DIV(cpu_t *cpu);

void RESTO(cpu_t *cpu);

void NEG(cpu_t *cpu);

void DESV(cpu_t *cpu);

void DESVZ(cpu_t *cpu);

void DESVNZ(cpu_t *cpu);

void LE(cpu_t *cpu);

void ESCR(cpu_t *cpu);

#endif // CPU_H
