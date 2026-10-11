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

HMODULE carregaClisitef()
{
    logger('i', "Carregando a lib...");

    HMODULE id = LoadLibraryA("libs/CliSiTef32I.dll");

    if (id == NULL)
    {
        logger('e', "erro ao carregar a lib: %lu", GetLastError());
        exit(EXIT_FAILURE);
    }

    logger('i', "Sucesso");
    return id;
}

void liberaClisitef(HMODULE *id)
{
    logger('i', "Liberando a lib...");

    if (!FreeLibrary(*id))
    {
        logger('e', "erro ao liberar a lib: %lu", GetLastError());
        exit(EXIT_FAILURE);
    }

    *id = NULL;

    logger('i', "Sucesso");
}

void recarregaClisitef(HMODULE *id)
{
    liberaClisitef(id);

    *id = carregaClisitef();
}

int configuraConexao(
    HMODULE id,
    char *buffer,
    size_t tamBuffer,
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    char *ParametrosAdicionais
)
{
    logger('i', "iniciando conexao com sitef...");

    if (id == NULL) {
        snprintf(buffer, tamBuffer, "a referencia a DLL esta vazia");
        return 1;
    }

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

    FARPROC funcAddr = GetProcAddress(id, "ConfiguraIntSiTefInterativoEx");
    ConfiguraIntSiTefInterativoEx configura = (ConfiguraIntSiTefInterativoEx)funcAddr;

    int response = configura(IPSiTef, IdLoja, IdTerminal, 0, ParametrosAdicionais);

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

    if (strlen(CupomFiscal) != 14) {
        snprintf(buffer, tamBuffer, "o cupomFiscal precisa ter 14 caracteres");
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