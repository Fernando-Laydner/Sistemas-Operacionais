#ifndef ERRO_H
#define ERRO_H

typedef enum {
    // Basic
    ERR_OK,

    // MEM
    ERR_MEM_END_INV,  // acesso a endereço de memória inválido

    // IO
    ERR_ES_DISP_INV,  // acesso a dispositivo inexistente
    ERR_ES_OP_INV,    // operação inválida em dispositivo

    // CPU
    ERR_CPU_PARADA,    // CPU executou instrução PARA
    ERR_CPU_INSTR_INV, // tentativa de execução de instrução inexistente
} err_t;

#endif // ERRO_H