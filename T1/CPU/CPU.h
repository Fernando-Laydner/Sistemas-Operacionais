#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include "CPU_API.h"
#include "Erro.h"
#include "Memory_API.h"
#include "IO_API.h"

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

#endif // CPU_H
