/*
 * leErro.h
 *
 *  Modified on: Jul, 2023
 *      Author: raphael oliveira
 */


/* Lê os dados formatados do arquivo ERRO */

#include <stdio.h> /* define FILE */
#include <stdlib.h>

void imprimeErro(TTransacao *transacao) {
    printf("\n**********************************************");
    printf("\nCliente de código ");
    printf("%d", transacao->codCliente);
    printf("\nTipo: ");
    printf("%c", transacao->tipoTransacao);
    printf("\nValor 01: ");
    printf("%s", transacao->valor01);
    printf("\nValor 02: ");
    printf("%s", transacao->valor02);
    printf("\n**********************************************");
}

TTransacao *leTransacaoErro(FILE *in) {
    TTransacao *transacao = (TTransacao *) malloc(sizeof(TTransacao));
    //fread retorna o total de elementos lidos com sucesso
    if (0 >= fread(&transacao->codCliente, sizeof(int), 1, in)) {
        free(transacao);
        return NULL;
    }
    fread(&transacao->tipoTransacao, sizeof(char), 1, in);
    fread(transacao->valor01, sizeof(char), sizeof(transacao->valor01), in);
    fread(transacao->valor02, sizeof(char), sizeof(transacao->valor02), in);
    return transacao;
}


void leErro(){
 FILE *fErro; /* ponteiro para arquivo */

 fErro = fopen("Erro.dat","rb");

 if(fErro == NULL) {
     printf("\n Erro ao abrir o arquivo ERRO");
     exit(1);
 }

 TTransacao *t;
 while ((t = leTransacaoErro(fErro)) != NULL)
	 imprimeErro(t);
 free(t);

 fclose(fErro);

}
