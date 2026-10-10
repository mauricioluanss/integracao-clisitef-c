#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "helpers.h"

void logger(const char level, const char *message, ...)
{
    const char *scope;
    char timestampBuffer[20];

    setaTimestamp(timestampBuffer, sizeof timestampBuffer);

    switch (level)
    {
    case 'i':
        scope = "info";
        break;
    case 'd':
        scope = "debug";
        break;
    case 'e':
        scope = "error";
        break;
    default:
        scope = "debug";
        break;
    }

    printf("%s - [%s] -> ", timestampBuffer, scope);

    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
}

void setaTimestamp(char *buffer, size_t tamanhoDoBuffer)
{
    time_t timestamp = time(NULL);
    struct tm *timestampEstruturado = localtime(&timestamp);

    strftime(buffer, tamanhoDoBuffer, "%d/%m/%Y %H:%M:%S", timestampEstruturado);
}