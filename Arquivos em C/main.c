//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 28/07/2022.

#include funcionario.h

void insere_5_funcionarios_aleatorios(FILE *out) {
    printf("Inserindo 5 funcionários no arquivo...");

    TFunc *f1 = funcionario(3, "Liz 03", "000.000.000-00", "01/01/1980", 3000);
    salva(f1, out);
    free(f1);
    TFunc *f2 = funcionario(4, "Raphael 04", "111.111.111-11", "01/01/1990", 500);
    salva(f2, out);
    free(f2);
    TFunc *f3 = funcionario(2, "Fátima 02", "222.222.222-22", "02/02/1980", 1000);
    salva(f3, out);
    free(f3);
    TFunc *f4 = funcionario(5, "Marcelo 05", "333.333.333-33", "03/03/1990", 1500);
    salva(f4, out);
    free(f4);
    TFunc *f5 = funcionario(1, "Silvia 01", "444.444.444-44", "04/04/1980", 900);
    salva(f5, out);
    free(f5);
}

void le_funcionarios(FILE *in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    TFunc *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

int main() {
    //declara ponteiro para arquivo
    FILE *in;
    //abre arquivo
    if ((in = fopen("funcionario.dat", "wb+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        //insere funcionários
        insere_5_funcionarios_aleatorios(in);
        //volta ao início do arquivo e lê os funcionários inseridos

        FILE *out;
        //abre arquivo
        if ((out = fopen("funcionarioOrdenado.dat", "wb+")) == NULL) {
            printf("Erro ao abrir arquivo\n");
            exit(1);
        }

        ordena_InsertionSort(in, out);
        ordena_BubbleSort(in, out);
        ordena_QuickSort(in, out);

        le_funcionarios(out);
        //fecha arquivo
        fclose(in);
        fclose(out);
    }
}

