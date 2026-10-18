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

int configura_conexao(
    CliSitef *clisitef,
    char *ip_sitef,
    char *id_loja,
    char *id_terminal,
    char *param_adic
);

int inicia_transacao(
    CliSitef *clisitef,
    int funcao,
    char *valor,
    char *param_adic
);

int continua_transacao(CliSitef *clisitef);

void finaliza_transacao(
    CliSitef *clisitef,
    short Confirma,
    char *CupomFiscal,
    char *ParamAdic
);

int get_transacoes_pendentes(
    CliSitef *clisitef,
    char *CupomFiscal
);

int get_versao_clisitef(HMODULE id);

void flush(void);

#endif
