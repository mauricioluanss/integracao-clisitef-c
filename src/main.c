#include <stdio.h>
#include <stdlib.h>
#include <libloaderapi.h>
#include "modules/clisitef/clisitef.h"
#include "modules/helpers/helpers.h"

int main()
{
    HMODULE id = carregaClisitef();
    FARPROC func = GetProcAddress(id, "ConfiguraIntSiTefInterativo");

    if (func == NULL)
    {
        logger('e', "erro ao chamar a funcao configura");
    }
    else
    {
        logger('i', "sucesso ao chamar a funcao configura");
    }

    logger('d', "Endereco: %p", (void*)func);
    recarregaClisitef(&id);
    liberaClisitef(&id);

    return 0;
}