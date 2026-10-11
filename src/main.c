#include <stdio.h>
#include <stdlib.h>
#include "modules/clisitef/clisitef.h"
#include "modules/helpers/helpers.h"
#include "enum/enum.h"

void menu(HMODULE *id)
{
    int option = 42;

    while (option != 3)
    {
        printf("menu - clisitef\n");
        printf("0 - carrega lib\n");
        printf("1 - liberar lib\n");
        printf("2 - recarregar lib\n");
        printf("3 - sair\n");
        printf("\nDigite a opcao: \n");
        scanf("%d", &option);

        switch (option)
        {
        case 0:
            *id = carregaClisitef();
            break;
        case 1:
            liberaClisitef(id);
            break;
        case 2:
            recarregaClisitef(id);
            break;
        case 3:
            break;
        default:
            printf("opcao invalida\n");
            break;
        }
    }
}

int main()
{
    HMODULE id = carregaClisitef();
    char buffer[200];

    int statusConexao = configuraConexao(id, buffer, sizeof(buffer), "127.0.0.1", "00000000", "00000001", "");

    if (statusConexao != 0) {
        logger('e', "%s", buffer);
        exit(EXIT_FAILURE);
    }


    int statusInicia = iniciaTransacao(id, buffer, sizeof(buffer), DEBITO, "100", "2026101116281201", "");

    if (statusInicia != 0 && statusInicia != 10000) {
        logger('e', "%s", buffer);
        exit(EXIT_FAILURE);
    }

    return 0;
}