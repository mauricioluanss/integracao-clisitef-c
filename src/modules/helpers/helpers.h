#ifndef HELPERS_H
#define HELPERS_H
#include <stddef.h>

void logger(const char level, const char *message, ...);
void set_timestamp(char *buffer, size_t tamanhoDoBuffer, const char *format);
const char *get_descricao_erro_configura(int status);
const char *get_descricao_erro_inicia(int status);
void print_menu(char *Titulo, int Comando, long TipoCampo, char *Buffer, int Continua);

#endif