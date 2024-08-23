/*
 * main.c
 *
 *  Modified on: Jul, 2023
 *      Author: raphael oliveira
 */

#include "cliente.h"
#include "transacao.h"

#include "criaMestre.h"
#include "leMestre.h"

#include "criaTransacoes.h"
#include "leTransacoes.h"

#include "balanceLine.h"

#include "leNovoMestre.h"
#include "leErro.h"

int main(){

	//**********************
	//Criando arquivo Mestre
	//**********************
	criaMestre();

	//**********************
	//Lendo o arquivo Mestre
	//**********************
	printf("\n===IMPRIMINDO O ARQUIVO MESTRE===");
	leMestre();

	//**********************
	//Criando arquivo Transações
	//**********************
	criaTransacoes();

	//**********************
	//Lendo o arquivo Transações
	//**********************
	printf("\n===IMPRIMINDO O ARQUIVO DE TRANSAÇÕES===");
	leTransacoes();


	FILE *fMestre, *fTransacoes, *fNovoMestre, *fErro; /* ponteiro para arquivos */

	fMestre = fopen("Mestre.dat","rb");
	fTransacoes = fopen("Transacoes.dat","rb");

	fNovoMestre = fopen("NovoMestre.dat","wb");
	fErro = fopen("Erro.dat","wb");

	 if((fMestre == NULL) || (fTransacoes == NULL)) {
	     printf("\n Erro ao abrir o arquivo");
	     exit(1);
	 }

	balanceLine(fMestre, fTransacoes, fNovoMestre, fErro);

	fclose(fMestre);
	fclose(fTransacoes);
	fclose(fNovoMestre);
	fclose(fErro);

	//IMPRIMIR O NOVO ARQUIVO MESTRE
	printf("\n===IMPRIMINDO O NOVO ARQUIVO MESTRE===");
	leNovoMestre();

	//IMPRIMIR O ARQUIVO DE ERRO
	printf("\n===IMPRIMINDO O ARQUIVO DE ERRO===");
	leErro();
	
	return 0;
}
