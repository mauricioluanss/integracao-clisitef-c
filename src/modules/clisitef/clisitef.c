#include <minwindef.h>
#include <errhandlingapi.h>
#include <string.h>
#include <stdio.h>
#include "clisitef.h"
#include "../helpers/helpers.h"
#include "../../enum/enum.h"


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
    char *ip_sitef,
    char *id_loja,
    char *id_terminal,
    char *param_adic
) {
    if (ip_sitef == NULL || strlen(ip_sitef) < 1) {
        logger('e', "campo 'ip_sitef' esta vazio");
        return -1;
    }

    if (strlen(id_loja) != 8) {
        logger('e', "campo 'id_loja' com tamanho incorreto");
        return -1;
    }

    if (strlen(id_terminal) != 8) {
        logger('e', "campo 'id_terminal' com tamanho incorreto");
        return -1;
    }

    logger(
        'd',
        "ip_sitef=[%s] id_loja=[%s] id_terminal=[%s] param_adic[%s]",
        ip_sitef, id_loja, id_terminal, param_adic
    );

    int response = clisitef->configura(
        ip_sitef,
        id_loja,
        id_terminal,
        0,
        param_adic
    );

    if (response != 0)
        logger('e', "erro configura: %s", get_descricao_erro_configura(response));

    return response;
}

int inicia_transacao(CliSitef *clisitef, int funcao, char *valor, char *param_adic) {
    char cupom_fiscal[17];
    char data_fiscal[9];
    char hora_fiscal[7];

    set_timestamp(cupom_fiscal, sizeof(cupom_fiscal), "%Y%m%d%H%M%S");

    memcpy(data_fiscal, cupom_fiscal, 8);
    memcpy(hora_fiscal, cupom_fiscal + 8, 6);
    data_fiscal[8] = '\0';
    hora_fiscal[6] = '\0';

    logger(
        'd',
        "funcao=[%d] valor=[%s] cupom_fiscal=[%s] data_fiscal=[%s] hora_fiscal=[%s] param_adic=[%s]",
        funcao, valor, cupom_fiscal, data_fiscal, hora_fiscal, param_adic
    );

    int response = clisitef->inicia(
        funcao,
        valor,
        cupom_fiscal,
        data_fiscal,
        hora_fiscal,
        "thaina",
        param_adic
    );

    if (response != 0 && response != 10000)
        logger('e', "erro inicia: %s", get_descricao_erro_inicia(response));

    return response;
}

int continua_transacao(CliSitef *clisitef) {
    int comando = 0;
    long tipo_campo = 0;
    short tam_minimo = 0;
    short tam_maximo = 0;
    char buffer[1024] = {0};
    int tam_buffer = sizeof(buffer);
    int continua = 0;
    int status_continua = 10000;

    while (status_continua == 10000) {
        status_continua = clisitef->continua(
            &comando,
            &tipo_campo,
            &tam_minimo,
            &tam_maximo,
            buffer,
            tam_buffer,
            continua    
        );

        logger(
            'd',
            "comando=[%d] tipo_campo=[%ld] tam_minimo=[%d] tam_maximo=[%d] buffer=[%s] continua=[%d] status_continua=[%d]",
            comando, tipo_campo, tam_minimo, tam_maximo, buffer, continua, status_continua
        );

        switch (comando) {
            case MSG_VISOR_OPERADOR:
            case MSG_VISOR_CLIENTE:
            case MSG_VISOR_AMBOS:
                break;

            case TITULO_MENU:
                break;

            case BUFFER_AGUARDA_REPOSTA:
                logger('i', "Digite 1(sim) e 2(nao): ");
                scanf("%s", buffer);
                break;

            default:
                //TODO: pensar...
                break;
        }
    }

    return status_continua;
}
