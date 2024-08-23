#include "lista_Encadeada.h"

TLista* cria_lista (){
	return NULL;
}

TLista* insere_inicio (TLista* li, int i) {
	TLista* novo = (TLista*) malloc(sizeof(TLista));
	novo->info = i;
	novo->prox = li;
	return novo;
}

void imprime (TLista* li) {
	TLista* p;
	for (p = li; p != NULL; p = p->prox)
		printf("info = %d\n", p->info);
}

TLista* insere_fim (TLista* li, int i) {
	TLista* novo = (TLista*) malloc(sizeof(TLista));
	novo->info = i;
	novo->prox = NULL;
	TLista* p = li;
	TLista* q = li;
	while (p != NULL) { /* encontra o ultimo elemento */
		q = p;
		p = p->prox;
	}
	if (q != NULL) /* se a lista original não estiver vazia */
		q->prox = novo;
	else
		li = novo;
	return li;
}

TLista* insere_ordenado (TLista* li, int i) {
	TLista* novo;
	TLista* ant = NULL; /* ponteiro para elemento anterior */
	TLista* p = li; /* ponteiro para percorrer a lista */
	/* procura posição de inserção */
	while (p != NULL && p->info < i) {
		ant = p;
		p = p->prox;
	}
	/* cria novo elemento */
	novo = (TLista*) malloc(sizeof(TLista));
	novo->info = i;
	/* encadeia elemento */
	if (ant == NULL) { /* insere elemento no início */
		novo->prox = li;
		li = novo;
	} else { /* insere elemento no meio da lista */
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return li;
}

TLista* insere_fim_recursivo (TLista* li, int i) {
	if (li == NULL) { /* parada da recursão: quando encontra-se o ultimo elemento */
		TLista* novo = (TLista*) malloc(sizeof(TLista));
		novo->info = i;
		novo->prox = NULL;
		li = novo;
	}else{
		li->prox = insere_fim_recursivo(li->prox, i);
	}
	return li;
}

//excluir um item da lista
TLista* exclui(TLista* li, int i) {
	//TODO
	return NULL;
}

//alterar um item da lista
TLista* altera(TLista* li, int vantigo, int vnovo) {
	//TODO
	return NULL;
}

//inserir recursivamente de forma ordenada
TLista* insere_ordenado_recursivo(TLista *li, TLista* ant, int i) {
	//TODO
	return NULL;
}

int main () {
	/* Insere elementos no inicio da lista */
	TLista *l1;
	l1 = cria_lista();
	l1 = insere_inicio(l1, 2);
	l1 = insere_inicio(l1, 3);
	l1 = insere_inicio(l1, 4);
	l1 = insere_inicio(l1, 5);
	printf("Lista 1:\n");
	imprime(l1);

	/* Insere elementos no fim da lista */
	TLista *l2;
	l2 = cria_lista();
	l2 = insere_fim(l2, 2);
	l2 = insere_fim(l2, 3);
	l2 = insere_fim(l2, 4);
	l2 = insere_fim(l2, 5);
	printf("\nLista 2:\n");
	imprime(l2);

	/* Insere elementos de forma que a lista esteja sempre ordenada */
	TLista *l3;
	l3 = cria_lista();
	l3 = insere_ordenado(l3, 3);
	l3 = insere_ordenado(l3, 4);
	l3 = insere_ordenado(l3, 5);
	l3 = insere_ordenado(l3, 2);
	printf("\nLista 3:\n");
	imprime(l3);

	/* Insere elementos de forma recursiva no fim da lista */
	TLista *l4;
	l4 = cria_lista();
	l4 = insere_fim_recursivo(l4, 2);
	l4 = insere_fim_recursivo(l4, 3);
	l4 = insere_fim_recursivo(l4, 4);
	l4 = insere_fim_recursivo(l4, 5);
	printf("\nLista 4:\n");
	imprime(l4);

	/* Insere elementos de forma recursiva ordenada na lista */
	TLista *l5;
	l5 = cria_lista();
	// l5 = insere_ordenado_recursivo(l5, NULL, 22);
	// l5 = insere_ordenado_recursivo(l5, NULL, 21);
	// l5 = insere_ordenado_recursivo(l5, NULL, 25);
	// l5 = insere_ordenado_recursivo(l5, NULL, 23);
	// l5 = insere_ordenado_recursivo(l5, NULL, 3);
	// l5 = insere_ordenado_recursivo(l5, NULL, 0);
	printf("\nLista 5:\n");
	imprime(l5);

	/* Insere elementos de forma recursiva no fim da lista */
	TLista *l6;
	l6 = cria_lista();
	l6 = insere_fim_recursivo(l6, 2);
	l6 = insere_fim_recursivo(l6, 3);
	l6 = insere_fim_recursivo(l6, 4);
	l6 = insere_fim_recursivo(l6, 5);
    l6 = insere_fim_recursivo(l6, 6);
	l6 = insere_fim_recursivo(l6, 8);

	// l6 = exclui(l6, 1);
	// l6 = exclui(l6, 2);
	// l6 = exclui(l6, 5);

	// l6 = altera(l6, 6, 10);
	// l6 = altera(l6, 7, 20);
	// l6 = altera(l6, 15, 30);
	printf("\nLista 6:\n");
	imprime(l6);

	return 0;
}
