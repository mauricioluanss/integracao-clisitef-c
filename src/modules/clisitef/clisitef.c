#include <stdlib.h>
#include <stdio.h>
#include <errhandlingapi.h>
#include <string.h>
#include "clisitef.h"
#include "../helpers/helpers.h"

/**
 *
 * Módulo que controla o ciclo de vida da DLL
 * CliSitef na memória, durante a execução do
 * programa.
 *
 *  */

int carrega_clisitef(CliSitef *clisitef) {
    logger('i', "Carregando a lib...");

    if (clisitef == NULL) {
        return 0;
    }

    clisitef->dll = LoadLibraryA("libs/CliSiTef32I.dll");

    if (clisitef->dll == NULL) {
        logger('e', "erro ao carregar a lib: %lu", GetLastError());
        return 0;
    }

    clisitef->configura =
        (ConfiguraIntSiTefInterativoEx)GetProcAddress(clisitef->dll, "ConfiguraIntSiTefInterativoEx");
    clisitef->inicia =
        (IniciaFuncaoSiTefInterativo)GetProcAddress(clisitef->dll, "IniciaFuncaoSiTefInterativo");
    clisitef->continua =
        (ContinuaFuncaoSiTefInterativo)GetProcAddress(clisitef->dll, "ContinuaFuncaoSiTefInterativo");
    clisitef->finaliza =
        (FinalizaFuncaoSiTefInterativo)GetProcAddress(clisitef->dll, "FinalizaFuncaoSiTefInterativo");

    if (
        !clisitef->configura ||
        !clisitef->inicia ||
        !clisitef->continua ||
        !clisitef->finaliza
    ) {
        logger('e', "uma ou mais funcoes nao foram encontradas na lib");
        libera_clisitef(clisitef);
        return 0;
    }

    logger('i', "Sucesso");
    return 1;
}

void limpa_instancia_clisitef(CliSitef *clisitef) {
    clisitef->dll = NULL;
    clisitef->configura = NULL;
    clisitef->inicia = NULL;
    clisitef->continua = NULL;
    clisitef->finaliza = NULL;

    logger('d', "instancia clisitef limpa");
} 

void libera_clisitef(CliSitef *clisitef) {
    logger('i', "Liberando a lib...");

    if (!FreeLibrary(clisitef->dll)) {
        logger('e', "erro ao liberar a lib: %lu", GetLastError());
    } else {
        limpa_instancia_clisitef(clisitef);
        logger('i', "Sucesso");
    }
}

void recarrega_clisitef(CliSitef *clisitef) {
    libera_clisitef(clisitef);
    carregaClisitef(clisitef);
}

int inicializa_sitef(CliSitef *clisitef) {
    if (!carrega_clisitef(&clisitef)) {
        return 0;
    }

    return 1;
}

int configuraConexao(
    CliSitef *clisitef,
    char *buffer,
    size_t tamBuffer,
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    char *ParametrosAdicionais
)
{
    logger('i', "iniciando conexao com sitef...");

    if (IPSiTef == NULL) {
        snprintf(buffer, tamBuffer, "campo 'IPSitef' esta vazio");
        return 1;
    }

    if (strlen(IdLoja) != 8) {
        snprintf(buffer, tamBuffer, "campo 'IdLoja' com tamanho incorreto");
        return 1;
    }

    if (strlen(IdTerminal) != 8) {
        snprintf(buffer, tamBuffer, "campo 'idTerminal' com tamanho incorreto");
        return 1;
    }

    logger('d', "Parametros: [%s - %s - %s - %s]", IPSiTef, IdLoja, IdTerminal, ParametrosAdicionais);

    int response = clisitef->configura(IPSiTef, IdLoja, IdTerminal, 0, ParametrosAdicionais);

    if (response != 0)
        snprintf(buffer, tamBuffer, "erro ao chamar a funcao configura: %s", getDescricaoErroConfigura(response));

    return response;
}

int iniciaTransacao(
    HMODULE id,
    char *buffer,
    size_t tamBuffer,
    int Funcao,
    char *Valor,
    char *CupomFiscal,
    char *ParamAdic
) {
    logger('i', "iniciando transacao...");

    if (id == NULL) {
        snprintf(buffer, tamBuffer, "a referencia a DLL esta vazia");
        return 1;
    }

    if (strlen(CupomFiscal) != 16) {
        snprintf(buffer, tamBuffer, "o cupomFiscal precisa ter 16 caracteres");
        return 1;
    }

    char DataFiscal[9];
    char HoraFiscal[7];

    memcpy(DataFiscal, CupomFiscal, 8);
    memcpy(HoraFiscal, CupomFiscal + 8, 6);
    
    DataFiscal[8] = '\0';
    HoraFiscal[6] = '\0';

    logger('i', "Parametros: [%d - %s - %s - %s - %s - %s]", Funcao, Valor, CupomFiscal, DataFiscal, HoraFiscal, ParamAdic);

    FARPROC funcAddr = GetProcAddress(id, "IniciaFuncaoSiTefInterativo");
    IniciaFuncaoSiTefInterativo inicia = (IniciaFuncaoSiTefInterativo)funcAddr;

    int response = inicia(Funcao, Valor, CupomFiscal, DataFiscal, HoraFiscal, "thaina", "");

    if (response != 0 && response != 10000)
        snprintf(buffer, tamBuffer, "erro ao chamar a funcao inicia: %s", getDescricaoErroInicia(response));

    return response;
}

int continuaTransacao(
    HMODULE id,
    int *Comando,
    long *TipoCampo,
    short *TamMinimo,
    short *TamMaximo,
    char *Buffer,
    int TamBuffer,
    int Continua
) {
    logger('i', "continua transacao...");

    // logger(
    //     'i',
    //     "Parametros: [%d - %d - %d - %d - %s - %d - %d]", *Comando, TipoCampo, TamMinimo, TamMaximo, Buffer, TamBuffer, Continua);

    FARPROC funcAddr = GetProcAddress(id, "ContinuaFuncaoSiTefInterativo");
    ContinuaFuncaoSiTefInterativo continua = (ContinuaFuncaoSiTefInterativo)funcAddr;

    return continua(Comando, TipoCampo, TamMinimo, TamMaximo, Buffer, TamBuffer, Continua);
}