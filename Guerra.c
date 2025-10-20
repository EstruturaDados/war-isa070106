#include <stdio.h>
#include <string.h>

/*
    ==============================================
       DESAFIO WAR ESTRUTURADO - NÍVEL NOVATO
       Estilo de saída igual ao mostrado no exemplo
    ==============================================

    Objetivo:
    Cadastrar 5 territórios com nome, cor do exército e número de tropas.
*/

// Definição da estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5];

    printf("==============================================\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
    printf("==============================================\n\n");

    // Cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o \n

        printf("Cor do Exercito (ex: Azul, Verde): ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remove o \n

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // limpa o \n deixado pelo scanf

        printf("\n");
    }

    // Exibição do resultado final
    printf("==============================================\n");
    printf("ESTADO ATUAL DO MAPA - TERRITORIOS CADASTRADOS\n");
    printf("==============================================\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Numero de Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------------\n");
    }

    printf("\nCadastro concluido com sucesso!\n");

    return 0;
}
