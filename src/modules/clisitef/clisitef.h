#ifndef CLISITEF_H
#define CLISITEF_H

#include <libloaderapi.h>

HMODULE carregaClisitef();
void liberaClisitef(HMODULE *id);
void recarregaClisitef(HMODULE *id);

#endif