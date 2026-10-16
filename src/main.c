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

void printMenu(
    int Comando,
    long TipoCampo,
    // short TamMinimo,
    // short TamMaximo,
    char *Buffer,
    // int TamBuffer,
    int Continua)
{
    printf("************************************************************\n");
    printf("*                  MENU INTERACAO SITEF                    *\n");
    printf("************************************************************\n");
    printf("* Comando: %i                                              *\n", Comando);
    printf("* TipoCampo: %lo                                           *\n", TipoCampo);
    printf("* Buffer: %s                                               *\n", Buffer);
    printf("* Continua: %d                                             *\n", Continua);
    printf("************************************************************\n");
}

int main() {
    CliSitef clisitef;

    carrega_clisitef(&clisitef);

    char buffer[200];

    int statusConexao = configuraConexao(
        &clisitef,
        buffer,
        sizeof(buffer),
        "127.0.0.1",
        "00000000",
        "00000001",
        ""
    );

    if (statusConexao != 0) {
        logger('e', "%s", buffer);
        exit(EXIT_FAILURE);
    }

    int statusInicia = iniciaTransacao(
        id,
        buffer,
        sizeof(buffer),
        DEBITO,
        "100",
        "2026101116281201",
        ""
    );

    if (statusInicia != 0 && statusInicia != 10000) {
        logger('e', "%s", buffer);
        exit(EXIT_FAILURE);
    }

    int Comando = 0;
    long TipoCampo = 0;
    short TamMinimo = 0;
    short TamMaximo = 0;
    char Buffer[1024] = {0};
    int TamBuffer = sizeof(Buffer);
    int Continua = 0;

    int statusContinua = 10000;

    while (statusContinua == 10000) {
        statusContinua = continuaTransacao(
            id,
            &Comando,
            &TipoCampo,
            &TamMinimo,
            &TamMaximo,
            Buffer,
            TamBuffer,
            Continua
        );

        // logger('i', "%s", printMenu(Comando, TipoCampo, Buffer, Continua));
        printMenu(Comando, TipoCampo, Buffer, Continua);

        switch (Comando) {
            case MSG_VISOR_OPERADOR:
            case MSG_VISOR_CLIENTE:
            case MSG_VISOR_AMBOS:
                printf("hello world");
                /* code */
                break;

            default:
                break;
        }
    }

    return 0;
}