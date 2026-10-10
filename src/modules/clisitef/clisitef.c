#include <stdlib.h>
#include <stdio.h>
#include <errhandlingapi.h>
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