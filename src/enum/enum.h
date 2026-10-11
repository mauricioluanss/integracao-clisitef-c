#ifndef ENUM_H
#define ENUM_H

typedef enum {
    CHEQUE = 1,
    DEBITO = 2,
    CREDITO = 3,
    CARTAO_BENEFICIO = 5,
    MENU_TRANSACOES_GERENCIAIS = 110,
    TESTE_COMUNICACAO = 111,
    MENU_REIMPRESSAO = 112,
    REIMPRESSAO_COMPROVANTE_ESPECIFICO = 113,
    REIMPRESSAO_ULTIMO_COMPROVANTE = 114,
    PRE_AUTORIZACAO = 115,
    CAPTURA_PRE_AUTORIZACAO = 116,
    CANCELAMENTO_NORMAL = 200,
    CANCELAMENTO_VENDA_CREDITO = 210,
    CANCELAMENTO_VENDA_DEBITO = 211,
    CONSULTA_SALDO = 600,
    FECHAMENTO = 999
} Funcoes;

#endif

 /* 
 1 Cheque 
2 Débito 
3 Crédito 
4 Fininvest 
5 Cartão Benefício 
6 Crédito Centralizado 
7 Cartão Combustível 
8 Parcele Mais Redecard 
10 Benefício Refeição Wappa 
11 Benefício Alimentação Wappa 
12 Cartão Infocard 
13 Pay Pass 
15 Venda com cartão Gift 
16 Débito para pagamento de carnê 
17 Crédito para pagamento de carnê 
28 Venda com Cartão Qualidade (ICI Card) 
100 Telemarketing: Inicia a coleta dos dados da transação no ponto necessário para tratar uma 
transação de cartão de crédito digitado 
101 Cancelamento de venda com cartão Qualidade (ICI Card) 
110 Abre o menu de transações Gerenciais 
111 Teste de comunicação com o SiTef 
112 Menu Re-impressão 
113 Re-impressão comprovante específico 
114 Re-impressão ultimo comprovante 
115 Pré-autorização 
116 Captura de pré-autorização 
117 Ajuste de pré-autorização 
118 Consulta de pré-autorização 
130 Consulta de transações pendentes no terminal 
131 Consulta de transações pendentes em um documento fiscal específico 
150 Consulta Bônus 
151 Consulta Saldo Cartão Presente 
152 Consulta Saldo Cartão Gift 
160 Consultas Cartão EMS 
161 Vendas Cartão EMS 
200 Cancelamento Normal: Inicia a coleta dos dados no ponto necessário para fazer o cancelamento de 
uma transação de débito ou crédito, sem ser necessário passar antes pelo menu de transações 
administrativas 
201 Cancelamento Telemarketing: Similar a modalidade 200 só que para a função de cancelamento de 
transação de crédito digitado 
202 Cancelamento Pré-autorização 
203 Cancelamento da Captura da Pré-autorização 
210 Cancelamento de venda com cartão de Crédito 
211 Cancelamento de venda com cartão de Débito 
212 Cancelamento de venda com cartão Combustível 
213 Cancelamento de Venda com Cartão Gift 
250 Cancelamento de Consulta Bônus 
251 Cancelamento Recarga Cartão Presente 
253 Cancelamento Acúmulo de Pontos Cartão Bônus 
254 Resgate de Pontos Cartão Bônus 
255 Cancelamento de Resgate de Pontos Cartão Bônus 
256 Acúmulo de Pontos Cartão Bônus 
257 Cancelamento Recarga Cartão Gift 
264 Recarga Cartão Gift 
265 Ativação Pagamento Vinculado Cartão Gift 
266 Consulta Cartão Gift 
267 Ativação Cartão Gift Sem Pagamento 
268 Ativação Cartão Gift Com Pagamento 
269 Ativação Desvinculada Cartão Gift 
310 Corresponde Bancário (Pagamento de Contas) 
311 Pagamento de Contas com Saque
312 Consulta para Pagamento Desvinculado (Genérico) 
313 Pagamento Desvinculado (Genérico) 
314 Recarga Pré Pago Corban SE com Saque 
315 Saque para Pagamento 
316 Cancelamento do pagamento desvinculado (genérico) 
317 Consulta Limites do Correspondente Bancário 
318 Recarga Pré Pago Bradesco 
319 Recarga Pré Pago Bradesco desvinculada do pagamento 
320 Recarga Pré Pago Corban SE 
321 Recarga Pré Pago Corban SE desvinculada do pagamento 
322 Depósito Identificado 
323 Transferência entre Contas 
324 Pague Fácil 
325 Revalidação de Senha INSS 
330 Transação de Débito com Saque (Compre e Saque) 
350 Venda Produto (Sem Valor) 
351 Cancelamento de Venda Produto (Sem Valor) 
400 Vale-Gás 
401 Validação Vale-Gás 
410 Troco Surpresa 
422 Adesão de Seguro 
430 Le Cartão Seguro (LeCartaoSeguro)  
431 Le Trilha Chip (LeTrilhaChipInterativoEx) 
500 Consulta Detalhada ACSP 
501 Consulta Detalhada Serasa 
600 Consulta Saldo 
601 Consulta Saldo Cartão de Débito 
602 Consulta Saldo Cartão de Crédito 
625 Venda Voucher/Ingresso com Fluxo de Coleta 
626 Consulta de Fornecedores e Produtos 
627 Venda Voucher sem Fluxo de Coleta 
628 Cancelamento de Venda Voucher 
657 Saque Crédito Transferência 
658 Saque Crédito 
660 Menu Saque IBI 
661 Consulta Saque Banco IBI 
662 Saque Banco IBI 
663 Saque GetNet 
664 Cancelamento Saque GetNet 
665 Resgate de Pontos 
667 Emissão de Pontos 
668 Cancelamento da Emissão de Pontos 
669 Carga de Pré Pago 
670 Cancelamento de Carga de Pré Pago 
671 Consulta Saque com Saque Banco IBI  
672 Cancelamento Saque Banco IBI 
680 Consulta Saldo Pré Pago 
698 Saque Débito 
700 Venda Oi Paggo 
701 Cancelamento Oi Paggo 
702 Pagamento de contas 
703 Cancelamento de Pagamento Cartão Benefício 
705 Pagamento de Fatura 
740 Consulta Parcelas Crédito Adm 
770 Carga de tabelas no pinpad 2 
771 Carga forçada de tabelas no pinpad (Local) 
772 Carga forçada de tabelas no pinpad (SiTef) 
775 Obtenção de informações do pinpad 3 
899 Recarga de cartão de crédito 
900 Cancelamento de recarga de cartão de crédito 
913 Alteração de Pré-Autorização 
928 Cancelamento Débito para Pagamento Carnê Rede Forçada 
943 Pagamento Fatura sem fatura vinculado 
944 Pagamento Fatura sem fatura desvinculado 
999 Fechamento 
1000 Voucher Papel
 */   