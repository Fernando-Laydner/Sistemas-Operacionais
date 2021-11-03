#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IO_API.h"
#include "CPU_API.h"
#include "Memory_API.h"

#define TAM 20 // o tamanho da memória

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

cpu_estado_t *cpu_estado(cpu_t *cpu){
    cpu_estado_t *temp;
    *temp = cpu->estado;
    return temp;
}

void cpu_altera_estado(cpu_t *cpu, cpu_estado_t *estado){
    // só isso?
    cpu->estado = *estado;
}

void cpu_altera_memoria(cpu_t *cpu, mem_t *mem){
    // só isso?
    cpu->mem = *mem;     
}

void cpu_altera_es(cpu_t *cpu, es_t *es){
    // só isso?
    cpu->es = *es;
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
    cpu_estado(cpu)->modo = mem_le(&cpu->mem, cpu_estado(cpu)->PC, &A1);
    if (cpu_estado(cpu)->modo != ERR_OK)
        return cpu_estado(cpu)->modo;

    switch (A1){
        case 0:
            cpu_estado(cpu)->modo = NOP();
        case 1:
            cpu_estado(cpu)->modo = PARA();
        case 2:
            cpu_estado(cpu)->modo = CARGI(cpu);
        case 3:
            cpu_estado(cpu)->modo = CARGM(cpu);
        case 4:
            cpu_estado(cpu)->modo = CARGX(cpu);
        case 5:
            cpu_estado(cpu)->modo = ARMM(cpu);
        case 6:
            cpu_estado(cpu)->modo = ARMX(cpu);
        case 7:
            cpu_estado(cpu)->modo = MVAX(cpu);
        case 8:
            cpu_estado(cpu)->modo = MVXA(cpu);
        case 9:
            cpu_estado(cpu)->modo = INCX(cpu);
        case 10:
            cpu_estado(cpu)->modo = SOMA(cpu);
        case 11:
            cpu_estado(cpu)->modo = SUB(cpu);
        case 12:
            cpu_estado(cpu)->modo = MULT(cpu);
        case 13:
            cpu_estado(cpu)->modo = DIV(cpu);
        case 14:
            cpu_estado(cpu)->modo = RESTO(cpu);
        case 15:
            cpu_estado(cpu)->modo = NEG(cpu);
        case 16:
            cpu_estado(cpu)->modo = DESV(cpu);
        case 17:
            cpu_estado(cpu)->modo = DESVZ(cpu);
        case 18:
            cpu_estado(cpu)->modo = DESVNZ(cpu);
        case 19:
            cpu_estado(cpu)->modo = LE(cpu);
        case 20:
            cpu_estado(cpu)->modo = ESCR(cpu);
        
        default:
            cpu_estado(cpu)->modo = ERR_CPU_INSTR_INV;
    }
    cpu_estado(cpu)->PC++;
    if (cpu_estado(cpu)->modo == ERR_OK && !(A1 == 0 || A1 == 1 || A1 == 7 || A1 == 8 || A1 == 9 || A1 == 15)){
        cpu_estado(cpu)->PC++;
    }
    return cpu_estado(cpu)->modo;
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