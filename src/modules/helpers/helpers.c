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

const char *getDescricaoErroConfigura(int status) {
    switch (status)
    {
    case 1: return "Endereco IP invalido ou nao resolvido";
    case 2: return "Codigo da loja invalido";
    case 3: return "Codigo de terminal invalido";
    case 6: return "Erro na inicializacao do Tcp/Ip";
    case 7: return "Falta de memoria";
    case 8: return "Nao encontrou a CliSiTef ou ela esta com problemas";
    case 9: return "Configuracao de servidores SiTef foi excedida.";
    case 10: return "Erro de acesso na pasta CliSiTef (possivel falta de permissao para escrita)";
    case 11: return "Dados invalidos passados pela automacao.";
    case 12: return "Modo seguro nao ativo (possivel falta de configuracao no servidor SiTef do arquivo .cha).";
    case 13: return "Caminho DLL invalido (o caminho completo das bibliotecas esta muito grande).";
    default: return "Erro desconhecido";
    }
}

const char *getDescricaoErroInicia(int status) {
    switch (status)
    {
    case -1: return "Modulo nao inicializado. O PDV tentou chamar alguma rotina sem antes executar a funcao configura.";
    case -2: return "Operacao cancelada pelo operador.";
    case -3: return "O parametro funcao / modalidade e inexistente/invalido.";
    case -4: return "Falta de memoria no PDV.";
    case -5: return "Sem comunicacao com o SiTef.";
    case -6: return "Operacao cancelada pelo usuario (no pinpad).";
    case -7: return "Reservado";
    case -8: return "A CliSiTef nao possui a implementacao da funcao necessaria, provavelmente esta desatualizada (a CliSiTefI e mais recente).";
    case -9: return "A automacao chamou a rotina ContinuaFuncaoSiTefInterativo sem antes iniciar uma funcao iterativa.";
    case -10: return "Algum parametro obrigatorio nao foi passado pela automacao comercial.";
    case -12: return "Erro na execucao da rotina iterativa. Provavelmente o processo iterativo anterior nao foi executado ate o final (enquanto o retorno for igual a 10000).";
    case -13: return "Documento fiscal nao encontrado nos registros da CliSiTef. Retornado em funcoes de consulta tais como ObtemQuantidadeTransacoesPendentes.";
    case -15: return "Operacao cancelada pela automacao comercial.";
    case -20: return "Parametro invalido passado para a funcao.";
    case -21: return "Utilizada uma palavra proibida, por exemplo SENHA, para coletar dados em aberto no pinpad. Por exemplo na funcao ObtemDadoPinpadDiretoEx.";
    case -25: return "Erro no Correspondente Bancario: Deve realizar sangria.";
    case -30: return "Erro de acesso ao arquivo. Certifique-se que o usuario que roda a aplicacao tem direitos de leitura/escrita.";
    case -40: return "Transacao negada pelo servidor SiTef.";
    case -41: return "Dados invalidos.";
    case -42: return "Reservado";
    case -43: return "Problema na execucao de alguma das rotinas no pinpad.";
    case -50: return "Transacao nao segura.";
    case -100: return "Erro interno do modulo.";
    default:
        if (status > 0) return "Negada pelo autorizador.";
        return "Erro detectado internamente pela rotina.";
    }
}
