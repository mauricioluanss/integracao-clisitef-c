#ifndef HELPERS_H
#define HELPERS_H

void logger(const char level, const char *message, ...);
void setaTimestamp(char *buffer, size_t tamanhoDoBuffer);
const char *getDescricaoErroConfigura(int status);
const char *getDescricaoErroInicia(int status);

#endif