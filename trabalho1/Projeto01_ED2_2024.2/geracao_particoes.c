//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 18/09/2021.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"
#include <stdlib.h>

typedef struct cliente_temp {
    Cliente *cliente;
    int congelado;
} ClientesTemp;

void descongelar(ClientesTemp *clientes, int M) {
    for(int i = 0; i < M; i++) {
        clientes[i].congelado = 0;
    }
}

int todos_congelados(ClientesTemp *clientes, int M) {
    for(int i = 0; i < M; i++) {
        if (!clientes[i].congelado) {
            return 0;
        }
    }
    return 1;
}

int buscar_menor_cliente_nao_congelado(ClientesTemp *clientes, int M) {
    int indice_menor = -1;

    for(int i = 0; i < M; i++) {
        if (!clientes[i].congelado) {
            if (indice_menor == -1 || clientes[i].cliente->cod_cliente < clientes[indice_menor].cliente->cod_cliente) {
                indice_menor = i;
            }
        }
    }

    return indice_menor;
}


int comparador(const void* a1, const void* b2) {
    Cliente* a = *(Cliente**)a1;
    Cliente* b = *(Cliente**)b2;
    return a->cod_cliente - b->cod_cliente;
}
 
int buscar_menor_cliente(Cliente **vetor_clientes, int M) {
    int menor = -1;

    for (int j = 0; j < M; j++) {
        if (vetor_clientes[j] != NULL) {
            menor = j;
            break;
        }
    }

    if (menor != -1) {
         for (int j = menor + 1; j < M; j++) {
            if (vetor_clientes[j] != NULL && vetor_clientes[j]->cod_cliente < vetor_clientes[menor]->cod_cliente) {
                menor = j;
            }
        }
    }

    return menor;
}


void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
	int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
    } else {

        //le primeiro cliente
        Cliente *cin = le_cliente(arq);

        while (!(fim)) {
            //le o arquivo e coloca no vetor
            Cliente *v[M];

            int i = 0;
            while (!feof(arq) && i < M) {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M) {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++) {
                Cliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente)) {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida\n");
            } else {
                for (int i = 0; i < M; i++) {
					salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq)) {
                fim = 1;
            }
        }
    }
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M) {
    FILE *entrada, *parcial;                                                                // criação dos ponteiros de arquivos

    if((entrada = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return;
    }                                                                                           // verificando se o arquivo foi aberto com sucesso

    ClientesTemp *clientes = (ClientesTemp*) malloc(M * sizeof(ClientesTemp));                  // criando e alocando o vetor de clientes com M posições
    Cliente *cliente_atual = le_cliente(entrada);                                               // le o primeiro cliente do arquivo

    int i = 0;
    while (!feof(entrada) && i < M) {                                                           // o loop se repete enquanto não chegar no final do arquivo e I<M
        clientes[i].cliente = cliente_atual;                                                    // aloca o cliente na posição I 
        clientes[i].congelado = 0;
        cliente_atual = le_cliente(entrada);
        i++;
    }

    M = (i != M) ? i : M;
 
    int continuar = 1;
    while (continuar) {                                                                         // loop paracriar partições
        if ((parcial = fopen(nome_arquivos_saida->nome, "wb")) == NULL) {   // abre o arquivo e verifica se foi aberto com sucesso
            printf("Erro ao abrir particao de saida\n");
            break;
        }

        int menor;
        while ((menor = buscar_menor_cliente_nao_congelado(clientes, M)) != -1) {   // variavel menor = chama a função para retornar o menor cliente não congelado
            salva_cliente(clientes[menor].cliente, parcial);                        // salva o cliente com o menor valor na partição

            if (cliente_atual != NULL) {                                            // verifica se a variavel atual é diferente de nullo
                if (cliente_atual->cod_cliente < clientes[menor].cliente->cod_cliente) {    // verifica se o ultimo cliente puxado é menor que o ultimo salvo
                    clientes[menor].congelado = 1;                                          // se for congelado rebece = true
                } else {
                    clientes[menor].congelado = 0;                                          // se não congelado recebe = false
                }
                
                clientes[menor].cliente = cliente_atual;                                    // adiciona o atual na no verto de clientes o registro verificado
                cliente_atual = le_cliente(entrada);                                        // chama um novo resgistor do arquivo de entrada
            } else {
                clientes[menor].congelado = 1;
            }

            if (todos_congelados(clientes, M)) {                                            // verifica se a quantidade de congelados não chegou no limite
                break;
            }
        }

        fclose(parcial);                                                                    // fecha a partição

        if (feof(entrada)) {                                                                // verifica se o arquivo de entrada não chegou no fim
            continuar = 0;                                                                  // se chegou encerrar o loop principal
        } else {                                                                            // see não descongela os arquivos e avança pra proxima partição 
            descongelar(clientes, M);
            nome_arquivos_saida = nome_arquivos_saida->prox;
        }
    }

    fclose(entrada);
    free(clientes);
}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n)
{
    Cliente** vetor_clientes = malloc(M * sizeof(Cliente));
    if (!vetor_clientes) 
    {
        printf("Erro ao alocar memoria\n");
        return;
    }

    char* nome_arquivo_saida = nome_arquivos_saida->nome;  //atribuição dos nomes ao ponteiro char
    
    FILE *in = fopen(nome_arquivo_entrada, "rb"),   // abertura dos arquivos
    *out = fopen(nome_arquivo_saida, "wb"), 
    *reservatorio = fopen("reservatorio.dat", "wb+"); // craição do arquivo de reservatorio para preenchimento posterior


    if (!in || !out || !reservatorio)               //verificando se os arquivos foram abertos com sucesso
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    int i, tamanho_reservatorio = 0;                // variaveis de controle do loop
    for (i = 0; i < M; i++) 
    {
        vetor_clientes[i] = le_cliente(in);         //alocação dos reistros no vetor  
        if (vetor_clientes[i] == NULL)              // verificando um possivel condição de para antes de antingir o numero desejado de resgistro coletados
        {
            M = i;
            break;
        }
    }

    while(1)                                       //loop principal do algoritmo 
    {
        int menor = buscar_menor_cliente(vetor_clientes, M); // pegando a posição do menor resgistor no vetor
        if(menor == -1) break;                               // verifica se menor não pegou valor -1
         
        int chave = vetor_clientes[menor]->cod_cliente;     // chave recebe o codigo do menor registro do vetor
        salva_cliente(vetor_clientes[menor], out);          // salva o cliente no arquivo de saida;
        free(vetor_clientes[menor]);                        // limpa os dados salvo na posição

        vetor_clientes[menor] = le_cliente(in);             // aloca um novo registro na posição que foi esvaziada
        while(vetor_clientes[menor] != NULL && vetor_clientes[menor]->cod_cliente < chave)  // loop verifica se o que foi alocado não é menor que o ultimo registro salvo
        {               
            salva_cliente(vetor_clientes[menor], reservatorio);                             // se a condição for verdadeira salva o cliente no reservatorio
            tamanho_reservatorio++;                                                         // incrementa no tamanho do reservatorio para atualizar a quantidade de registros salvos no reservatorio

            if(tamanho_reservatorio == n) break;                                            // verifica se o reservatorio já atingiu o tamanho maximo

            free(vetor_clientes[menor]);                                                    // libera espaço no reservatorio 
            vetor_clientes[menor] = le_cliente(in);                                         // aloca um novo cliente no menor valor do reservatori;
        }

        if(tamanho_reservatorio == n)                                                       // verifica se o reservatorio está cheio e se estiver ordena os registro 
        {
            qsort(vetor_clientes, M, sizeof(Cliente*), comparador);
            
            for(i = 1; i < M; i++)                                                          // salva os cliente do reservatorio no arquivo
            {
                salva_cliente(vetor_clientes[i], out);
                free(vetor_clientes[i]);
            }   

            fclose(out);                                                                    // fecha o arquivo de saida
            fclose(reservatorio);                                                           // fecha o arquivo do reservatório
            reservatorio = fopen("reservatorio.dat", "rb+");                                // cria um novo arquivo de reservatório substituindo o que já existia

            i = 0;
            while(i < M && (vetor_clientes[i] = le_cliente(reservatorio)) != NULL)          // preenche o reservatório
            {
                i++;
            }

            M = tamanho_reservatorio;                                                        // define o tamanho de M com o tamanho do reservatório
            fclose(reservatorio);
            nome_arquivos_saida = nome_arquivos_saida->prox;                                 // puxa o prox nome do arquivo para
            nome_arquivo_saida = nome_arquivos_saida->nome;                                  // define o nome da nova partição
            
            out = fopen(nome_arquivo_saida, "wb");                                           //abre o arquivo de saida
            reservatorio = fopen("reservatorio.dat", "wb+");                                 // abre um novo arquivo de reservatorio para escrita 
            tamanho_reservatorio = 0;                                                        // reseta o tamanho do reservat´roio
        }
    }

    fclose(in);
    fclose(reservatorio);
    fclose(out);
}

