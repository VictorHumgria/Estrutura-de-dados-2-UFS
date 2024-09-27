/*
JOAO VICTOR SILVA DE HUNGRIA / 202000060933 
JOÃO VICTOR MENESES SOUZA / 202300133617
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore_b.h"
#include "metadados.h"
#include "no.h"

#define _fseek(file, bytes) fseek(file, bytes, SEEK_SET)
#define NULO -1

/* Função Busca Inicio */
int busca_binaria(Cliente** array, int cod_cliente, int tamanho, int* indice_filho, int* encontrado) {
    int esquerda = 0, direita = tamanho - 1;
    while (esquerda <= direita) {
        *indice_filho = esquerda + (direita - esquerda) / 2;
        if (array[*indice_filho]->cod_cliente == cod_cliente) {
			*encontrado = 1;
			return *indice_filho;
        } else if (array[*indice_filho]->cod_cliente > cod_cliente) {
			direita = *indice_filho - 1;
        } else {
			esquerda = *indice_filho + 1;
        }
    }
	
    *encontrado = 0;
    return esquerda;
}

int busca_interna(No* pagina, int cod_cliente, int* indice_filho, int* encontrado) {
    int pos = busca_binaria(pagina->clientes, cod_cliente, pagina->m, indice_filho, encontrado);
    if (!*encontrado && pagina->clientes[*indice_filho]->cod_cliente < cod_cliente) {
		(*indice_filho)++;
    }
	
    return pos;
}

int busca_auxiliar(char* nome_arquivo_dados, int cod_cliente, int* encontrado, int* ponteiro) {
    FILE* arquivo = fopen(nome_arquivo_dados, "rb");
    _fseek(arquivo, *ponteiro);
    No* pagina = le_no(arquivo);

    int proximo_filho = 0;
    int resultado = busca_interna(pagina, cod_cliente, &proximo_filho, encontrado);

    while (!*encontrado && pagina->p[proximo_filho] != NULO) {
		*ponteiro = pagina->p[proximo_filho];
		libera_no(pagina);
		_fseek(arquivo, *ponteiro);
		pagina = le_no(arquivo);
		resultado = busca_interna(pagina, cod_cliente, &proximo_filho, encontrado);
    }

    fclose(arquivo);
    return resultado;
}

int busca(int cod_cliente, char* nome_arquivo_metadados, char* nome_arquivo_dados, int* ponteiro, int* encontrado) {
    FILE* arquivo_metadados = fopen(nome_arquivo_metadados, "rb");
    Metadados* metadados = le_metadados(arquivo_metadados);
    *ponteiro = metadados->pont_raiz;
    free(metadados);
    fclose(arquivo_metadados);

    return busca_auxiliar(nome_arquivo_dados, cod_cliente, encontrado, ponteiro);
}
/* Função Busca Fim */


/* Função Insere Inicio */
int insercao_ordenada(Cliente** array, int tamanho, Cliente* novo_cliente) {
    int i = tamanho - 1;
    while (i >= 0 && array[i]->cod_cliente > novo_cliente->cod_cliente) {
		array[i + 1] = array[i];
		i--;
    }
    array[i + 1] = novo_cliente;
    return i + 1;
}

void copiar_dados(Cliente* array[2 * D + 1], No* filho_esquerdo, No* filho_direito) {
    for (int i = 0; i < D; i++) {
		filho_esquerdo->clientes[i] = array[i];
		filho_direito->clientes[i] = array[i + D + 1];
    }
    for (int i = D; i < D * 2; i++) {
		filho_direito->clientes[i] = NULL;
    }
}

int distribuir_pai_e_filhos(Cliente* array[2 * D + 1], Cliente* cliente_sobe, Metadados* metadados, No* pai, No* filho_esquerdo, No* filho_direito) {
    int posicao = insercao_ordenada(pai->clientes, pai->m, cliente_sobe);
    pai->m++;
    filho_esquerdo->m = D;

    for (int i = pai->m; i > posicao; i--) {
		pai->p[i + 1] = pai->p[i];
    }
    pai->p[posicao + 1] = metadados->pont_prox_no_livre;
    copiar_dados(array, filho_esquerdo, filho_direito);

    return posicao;
}

int dividir_raiz(char* nome_arquivo_dados, Cliente* array[2 * D + 1], No* antiga_raiz, Metadados* metadados) {
    FILE* arquivo = fopen(nome_arquivo_dados, "wb+");
    No* novo_filho = no(D, metadados->pont_prox_no_livre);
    No* nova_raiz = no(1, metadados->pont_prox_no_livre + tamanho_no());

    nova_raiz->clientes[0] = array[D];
    nova_raiz->pont_pai = -1;
    nova_raiz->p[0] = 0;
    nova_raiz->p[1] = metadados->pont_prox_no_livre;

    antiga_raiz->pont_pai = metadados->pont_prox_no_livre + tamanho_no();
    novo_filho->pont_pai = metadados->pont_prox_no_livre + tamanho_no();
    antiga_raiz->m = D;

    for (int i = D; i < D * 2; i++) {
		antiga_raiz->clientes[i] = NULL;
    }
    copiar_dados(array, antiga_raiz, novo_filho);

    for (int i = 0; i < novo_filho->m + 1; i++) {
		novo_filho->p[i] = -1;
		antiga_raiz->p[i] = -1;
    }

    _fseek(arquivo, metadados->pont_raiz);
    salva_no(antiga_raiz, arquivo);

    _fseek(arquivo, metadados->pont_prox_no_livre);
    salva_no(novo_filho, arquivo);

    _fseek(arquivo, metadados->pont_prox_no_livre + tamanho_no());
    salva_no(nova_raiz, arquivo);

    metadados->pont_raiz = metadados->pont_prox_no_livre + tamanho_no();
    metadados->pont_prox_no_livre += tamanho_no() * 2;

    libera_no(novo_filho);
    libera_no(nova_raiz);
    fclose(arquivo);
    return 0;
}

int particionar_folha(char* nome_arquivo_dados, Metadados* metadados, No* pagina, Cliente* novo_cliente) {
    FILE* arquivo = fopen(nome_arquivo_dados, "rb+");
    Cliente* array[2 * D + 1];

    for (int i = 0; i < 4; i++) {
            array[i] = pagina->clientes[i];
    }
    insercao_ordenada(array, 2 * D, novo_cliente);

    int pos = 0;
    Cliente* cliente_sobe = array[D];

    if (pagina->pont_pai != NULO) {
		_fseek(arquivo, pagina->pont_pai);
		No* pai = le_no(arquivo);
		No* novo = no(D, pagina->pont_pai);

		if (pai->m < (2 * D)) {
			int posicao = distribuir_pai_e_filhos(array, cliente_sobe, metadados, pai, pagina, novo);
			pos = pai->p[posicao];

			_fseek(arquivo, pagina->pont_pai);
			salva_no(pai, arquivo);

			_fseek(arquivo, pai->p[posicao]);
			salva_no(pagina, arquivo);

			_fseek(arquivo, metadados->pont_prox_no_livre);
			salva_no(novo, arquivo);
		} else {
				// Propagação...
		}

		libera_no(pai);
    } else {
		pos = dividir_raiz(nome_arquivo_dados, array, pagina, metadados);
    }

    fclose(arquivo);
    return pos;
}

int insere(int cod_cliente, char* nome_cliente, char* nome_arquivo_metadados, char* nome_arquivo_dados) {
    int encontrado, ponteiro;
    int posicao = busca(cod_cliente, nome_arquivo_metadados, nome_arquivo_dados, &ponteiro, &encontrado);
    if (encontrado) {
		return -1;
    }

    FILE* arquivo = fopen(nome_arquivo_dados, "rb+");
    _fseek(arquivo, ponteiro);
    No* pagina = le_no(arquivo);

    if (pagina->m >= 2 * D) {
		FILE* arquivo_metadados = fopen(nome_arquivo_metadados, "rb+");
		Metadados* metadados = le_metadados(arquivo_metadados);

		ponteiro = particionar_folha(nome_arquivo_dados, metadados, pagina, cliente(cod_cliente, nome_cliente));
		rewind(arquivo_metadados);

		salva_metadados(metadados, arquivo_metadados);
		fclose(arquivo_metadados);
		free(metadados);
    } else {
		posicao = insercao_ordenada(pagina->clientes, pagina->m, cliente(cod_cliente, nome_cliente));
		pagina->m++;
		_fseek(arquivo, ponteiro);
		salva_no(pagina, arquivo);
    }

    libera_no(pagina);
    fclose(arquivo);

    return ponteiro;
}
/* Função Insere  Fim */

/* Função Exclui Inicio */
void remover_cliente(No* pagina, int indice) {
    memcpy(&pagina->clientes[indice], &pagina->clientes[indice + 1], sizeof(Cliente*) * (pagina->m - indice - 1));
    memcpy(&pagina->p[indice + 1], &pagina->p[indice + 2], sizeof(int) * (pagina->m - indice));
    pagina->clientes[pagina->m - 1] = NULL;
    pagina->p[pagina->m--] = NULO;
}

void concatenar(No* P, No* W, No* Q) {
    int tamanho = P->m + Q->m + 1;
    Cliente** array = (Cliente**)malloc(sizeof(Cliente*) * tamanho);

    int ponteiro_pai = 0;
    while (W->clientes[ponteiro_pai]->cod_cliente < P->clientes[0]->cod_cliente) {
		ponteiro_pai++;
    }

    int i = 0;
    while (i < P->m) {
		array[i] = P->clientes[i];
		i++;
    }

    for (int j = 0; j < Q->m; j++) {
		array[i] = Q->clientes[j];
		i++;
    }

    insercao_ordenada(array, tamanho - 1, W->clientes[ponteiro_pai]);
    remover_cliente(W, ponteiro_pai);

    memcpy(P->clientes, array, tamanho * sizeof(Cliente*));
    P->m = tamanho;
}

void redistribuir(No* P, No* W, No* Q) {
    int tamanho = P->m + Q->m + 1;
    Cliente** array = (Cliente**)malloc(sizeof(Cliente*) * tamanho);

    int ponteiro_pai = 0;
    while (W->clientes[ponteiro_pai]->cod_cliente < P->clientes[0]->cod_cliente) {
		ponteiro_pai++;
    }

    int i = 0;
    while (i < P->m) {
		array[i] = P->clientes[i];
		i++;
    }

    array[i++] = W->clientes[ponteiro_pai];

    for (int j = 0; j < Q->m; j++) {
		array[i] = Q->clientes[j];
		i++;
    }

    W->clientes[ponteiro_pai] = array[D];
    memset(P->clientes, 0, sizeof(Cliente*) * P->m);
    memset(Q->clientes, 0, sizeof(Cliente*) * Q->m);

    P->m = D;
    Q->m = tamanho - D - 1;

    memcpy(P->clientes, array, D * sizeof(Cliente*));
    memcpy(Q->clientes, array + D + 1, Q->m * sizeof(Cliente*));

    free(array);
}

int exclui(int cod_cliente, char* nome_arquivo_metadados, char* nome_arquivo_dados) {
    int encontrado, posicao, indice = busca(cod_cliente, nome_arquivo_metadados, nome_arquivo_dados, &posicao, &encontrado);
    if (!encontrado) {
		return -1;
    }

    FILE* arquivo = fopen(nome_arquivo_dados, "rb+");
    _fseek(arquivo, posicao);
    No* pagina = le_no(arquivo);

    if (pagina->p[0] != NULO) {
        _fseek(arquivo, pagina->p[indice + 1]);
        No* filho = le_no(arquivo);

        pagina->clientes[indice] = filho->clientes[0];
        remover_cliente(filho, 0);

        _fseek(arquivo, pagina->p[indice + 1]);
        salva_no(filho, arquivo);
    } else {
        remover_cliente(pagina, indice);

        if (pagina->m < D) {
            _fseek(arquivo, pagina->pont_pai);
            No* pai = le_no(arquivo);

            int end_Q = 0;
            for (int i = 0; i < pai->m + 1; i++) {
				if (pai->p[i] == posicao) {
					end_Q = pai->p[i + 1];
					break;
				}
            }
			
            _fseek(arquivo, end_Q);
            No* Q = le_no(arquivo);

            if ((pagina->m + Q->m) < 2 * D) {
				concatenar(pagina, pai, Q);
				free(Q);
				Q = NULL;
            } else {
				redistribuir(pagina, pai, Q);
            }

            _fseek(arquivo, pagina->pont_pai);
            salva_no(pai, arquivo);

            _fseek(arquivo, end_Q);
            if (Q) salva_no(Q, arquivo);
            else free(Q);

            _fseek(arquivo, posicao);
            salva_no(pagina, arquivo);

            libera_no(pai);
        }
    }

    _fseek(arquivo, posicao);
    salva_no(pagina, arquivo);

    libera_no(pagina);
    fclose(arquivo);

    return posicao;
}
/* Função Exclui Fim */

//gcc cliente.c lista_clientes.c lista_nos.c metadados.c no.c -o test_arvore_b && test_arvore_b   