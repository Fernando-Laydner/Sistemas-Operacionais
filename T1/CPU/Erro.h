#ifndef ERRO_H
#define ERRO_H

typedef enum {
    // Basic
    ERR_OK = 0,

    // MEM
    ERR_MEM_END_INV = 1,  // acesso a endereço de memória inválido

    // IO
    ERR_ES_DISP_INV = 2,  // acesso a dispositivo inexistente
    ERR_ES_OP_INV = 3,    // operação inválida em dispositivo

    // CPU
    ERR_CPU_PARADA = 4,    // CPU executou instrução PARA
    ERR_CPU_INSTR_INV = 5, // tentativa de execução de instrução inexistente
} err_t;

#endif // ERRO_H
