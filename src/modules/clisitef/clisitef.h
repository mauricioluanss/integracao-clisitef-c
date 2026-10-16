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

typedef struct {
    HMODULE dll;
    ConfiguraIntSiTefInterativoEx configura;
    IniciaFuncaoSiTefInterativo inicia;
    ContinuaFuncaoSiTefInterativo continua;
    FinalizaFuncaoSiTefInterativo finaliza;
} CliSitef;

int carrega_clisitef(CliSitef *clisitef);

void limpa_instancia_clisitef(CliSitef *clisitef);

void libera_clisitef(CliSitef *clisitef);

void recarrega_clisitef(CliSitef *clisitef);

int configuraConexao(
    CliSitef *clisitef,
    char *buffer,
    size_t tamBuffer,
    char *IPSiTef,
    char *IdLoja,
    char *IdTerminal,
    char *ParametrosAdicionais
);

int iniciaTransacao(
    HMODULE id,
    char *buffer,
    size_t tamBuffer,
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