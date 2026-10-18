#include <stdlib.h>
#include <string.h>
#include "modules/clisitef/clisitef.h"
#include "modules/helpers/helpers.h"
#include "enum/enum.h"


void set_args(
    int argc,
    char const *argv[],
    char **ip_sitef,
    char **id_loja,
    char **id_terminal,
    char **param_adic
) {
    if (argc > 1 && strlen(argv[1]) > 0) *ip_sitef = argv[1];
    if (argc > 2 && strlen(argv[2]) > 0) *id_loja = argv[2];
    if (argc > 3 && strlen(argv[3]) > 0) *id_terminal = argv[3];
    if (argc > 4 && strlen(argv[4]) > 0) *param_adic = argv[4];
}

int main(int argc, char const *argv[]) {
    CliSitef clisitef;
    
    char *ip_sitef = "127.0.0.1";
    char *id_loja = "00000000";
    char *id_terminal = "00000001";
    char *param_adic = "";

    if (argc > 1) {
        set_args(
            argc,
            argv,
            &ip_sitef,
            &id_loja,
            &id_terminal,
            &param_adic
        );
    }

    if (!carrega_clisitef(&clisitef))
        exit(EXIT_FAILURE);

    logger('i', "iniciando conexao com sitef...");
    int status_configura = configura_conexao(
        &clisitef,
        ip_sitef,
        id_loja,
        id_terminal,
        param_adic
    );

    if (status_configura != 0) {
        libera_clisitef(&clisitef);
        exit(EXIT_FAILURE);
    }

    logger('i', "iniciando transacao...");

    int status_inicia = inicia_transacao(
        &clisitef,
        DEBITO,
        "100",
        ""
    );

    if (status_inicia != 0 && status_inicia != 10000) {
        libera_clisitef(&clisitef);
        exit(EXIT_FAILURE);
    }

    logger('i', "continua transacao...");

    int status_continua = continua_transacao(&clisitef);
    libera_clisitef(&clisitef);

    return status_continua;
}
