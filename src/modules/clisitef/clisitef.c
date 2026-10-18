#include <minwindef.h>
#include <errhandlingapi.h>
#include <string.h>
#include "clisitef.h"
#include "../helpers/helpers.h"


int carrega_clisitef(CliSitef *clisitef) {
    logger('i', "Carregando a lib...");

    if (clisitef == NULL)
        return 0;

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
    carrega_clisitef(clisitef);
}

int configura_conexao(
    CliSitef *clisitef,
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    char *ParametrosAdicionais
) {
    logger('i', "iniciando conexao com sitef...");

    if (IPSiTef == NULL || strlen(IPSiTef) < 1) {
        logger('e', "campo 'IPSitef' esta vazio");
        return -1;
    }

    if (strlen(IdLoja) != 8) {
        logger('e', "campo 'IdLoja' com tamanho incorreto");
        return -1;
    }

    if (strlen(IdTerminal) != 8) {
        logger('e', "campo 'idTerminal' com tamanho incorreto");
        return -1;
    }

    logger(
        'd',
        "Params: [%s - %s - %s - %s]",
        IPSiTef, IdLoja, IdTerminal, ParametrosAdicionais
    );

    int response = clisitef->configura(
        IPSiTef,
        IdLoja,
        IdTerminal,
        0,
        ParametrosAdicionais
    );

    if (response != 0)
        logger('e', "erro configura: %s", getDescricaoErroConfigura(response));

    return response;
}

int inicia_transacao(
    CliSitef *clisitef,
    int Funcao,
    char *Valor,
    char *CupomFiscal,
    char *ParamAdic
) {
    logger('i', "iniciando transacao...");

    if (strlen(CupomFiscal) != 16) {
        logger('e', "o cupomFiscal precisa ter 16 caracteres");
        return -1;
    }

    char DataFiscal[9];
    char HoraFiscal[7];
    memcpy(DataFiscal, CupomFiscal, 8);
    memcpy(HoraFiscal, CupomFiscal + 8, 6);
    DataFiscal[8] = '\0';
    HoraFiscal[6] = '\0';

    logger(
        'd',
        "Params: [%d - %s - %s - %s - %s - %s - %s]",
        Funcao, Valor, CupomFiscal, DataFiscal, HoraFiscal, "thaina", ParamAdic
    );

    int response = clisitef->inicia(
        Funcao,
        Valor,
        CupomFiscal,
        DataFiscal,
        HoraFiscal,
        "thaina",
        ParamAdic
    );

    if (response != 0 && response != 10000)
        logger('e', "erro inicia: %s", getDescricaoErroInicia(response));

    return response;
}

int continua_transacao(
    CliSitef *clisitef,
    int *Comando,
    long *TipoCampo,
    short *TamMinimo,
    short *TamMaximo,
    char *Buffer,
    int TamBuffer,
    int Continua
) {
    logger('i', "continua transacao...");

    int response = clisitef->continua(
        Comando,
        TipoCampo,
        TamMinimo,
        TamMaximo,
        Buffer,
        TamBuffer,
        Continua
    );

    if (response != 10000)
        logger('e', "erro continua: %s", Buffer);

    return response;
}
