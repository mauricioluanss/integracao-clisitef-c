#ifndef HELPERS_H
#define HELPERS_H
#include <stddef.h>

void logger(const char level, const char *message, ...);
void setaTimestamp(char *buffer, size_t tamanhoDoBuffer);
const char *getDescricaoErroConfigura(int status);
const char *getDescricaoErroInicia(int status);
void print_menu(char *Titulo, int Comando, long TipoCampo, char *Buffer, int Continua);

#endif