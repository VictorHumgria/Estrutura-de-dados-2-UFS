/*
 * balanceLine.h
 *
 *  Modified on: Jul, 2023
 *      Author: raphael oliveira
 */


#include <stdio.h> /* define FILE */
#include <stdlib.h>

void balanceLine(FILE *fMestre, FILE *fTransacao, FILE *fNovoMestre, FILE *fErro){
	fopen(fMestre);
	fopen(fTransacao);
	fopen(fNovoMestre);
	fopen(fErro);

	TCliente *oldMestre = (TCliente *) malloc(sizeof(TCliente));
	TCliente *newMestre = (TCliente *) malloc(sizeof(TCliente));
	rewind(fMestre);
	rewind(fTransacao);
        fMestre = fopen("fMestre.txt", "r");
    fTransacao = fopen("fTransacao.txt", "r");
    fNovoMestre = fopen("fNovoMestre.txt", "w");

    // Verifica se os arquivos foram abertos corretamente
    if (!fMestre || !fTransacao || !fNovoMestre) {
        erro("Erro ao abrir arquivo");
    }

    // Lê os arquivos
    while (1) {
        lerArquivoMestre(&regMestre, fMestre);
        lerArquivoTransacao(&regTransacao, fTransacao);

        // Verifica se os arquivos chegaram ao fim
        if (feof(fMestre) && feof(fTransacao)) {
            break;
        }

        // Processa a operação
        switch (regTransacao.operacao) {
            case 'I': // Isenção
                // Não grava nada no arquivo de saída
                break;
            case 'E': // Exclusão
                // Não grava nada no arquivo de saída
                break;
            case 'C': // Alteração
                regMestre.chave = regTransacao.chave;
                strcpy(regMestre.filler, regTransacao.filler);
                gravarArquivoNovoMestre(&regMestre, fNovoMestre);
                totalGravados++;
                break;
            default:
                erro("Operação inválida");
        }
    }

    // Fecha os arquivos
    fclose(fMestre);
    fclose(fTransacao);
    fclose(fNovoMestre);

    // Imprime os totais
    printf("Total de lidos arquivo Mestre: %d\n", totalLidosMestre);
    printf("Total de lidos arquivo Transacao: %d\n", totalLidosTransacao);
    printf("Total gravados: %d\n", totalGravados);
}
