#ifndef CLISITEF_H
#define CLISITEF_H

#include <libloaderapi.h>

/**
 * Abaixo as definições de tipos de ponteiro para funções da CliSitef,
 * usando a convenção __stdcall.
 */

typedef int(__stdcall *ConfiguraIntSiTefInterativoEx)(
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    short Reservado,
    char *ParametrosAdicionais
);

typedef int(__stdcall *IniciaFuncaoSiTefInterativo)(
    int Funcao,
    char *Valor,
    char *CupomFiscal,
    char *DataFiscal,
    char *HoraFiscal,
    char *Operador,
    char *ParamAdic
);

typedef int(__stdcall *ContinuaFuncaoSiTefInterativo)(
    int *Comando,
    long *TipoCampo,
    short *TamMinimo,
    short *TamMaximo,
    char *Buffer,
    int TamBuffer,
    int Continua
);

typedef void(__stdcall *FinalizaFuncaoSiTefInterativo)(
    short Confirma,
    char *CupomFiscal,
    char *DataFiscal,
    char *HoraFiscal,
    char *ParamAdic
);

typedef int(__stdcall *ObtemQuantidadeTransacoesPendentes)(
    char *DataFiscal,
    char *CupomFiscal
);

typedef int(__stdcall *ObtemVersao)(
    char *VersaoCliSiTef,
    char *VersaoCliSiTefI
);

typedef void(__stdcall *DescarregaMensagens)(void);


/**
 * Abaixo definições das funções de cliclo de vida
 * da CliSitef na memoria.
 */

HMODULE carregaClisitef();

void liberaClisitef(HMODULE *id);

void recarregaClisitef(HMODULE *id);

int configuraConexao(
    HMODULE id,
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    char *ParametrosAdicionais
);

int iniciaTransacao(
    HMODULE id,
    int Funcao,
    char *Valor,
    char *CupomFiscal,
    char *ParamAdic
);

int continuaTransacao(
    HMODULE id,
    int *Comando,
    long *TipoCampo,
    short *TamMinimo,
    short *TamMaximo,
    char *Buffer,
    int TamBuffer,
    int Continua
);

void finalizaTransacao(
    HMODULE id,
    short Confirma,
    char *CupomFiscal,
    char *ParamAdic
);

int getTransacoesPendentes(
    HMODULE id,
    char *CupomFiscal
);

int getVersaoClisitef(HMODULE id);

void flush(void);

#endif