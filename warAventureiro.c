#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    ===============================================
       DESAFIO WAR ESTRUTURADO - NÍVEL AVENTUREIRO
    ===============================================

    Funcionalidades:
    - Cadastro dinâmico de territórios (calloc)
    - Simulação de ataques com dados (rand)
    - Atualização de tropas e cor
    - Uso de ponteiros e modularização
*/

// Definição da estrutura Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ----------- PROTÓTIPOS DAS FUNÇÕES ------------
Territorio* cadastrarTerritorios(int* qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// ----------------- FUNÇÃO PRINCIPAL -----------------
int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    int qtdTerritorios;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);
    getchar(); // limpa o buffer

    Territorio* mapa = cadastrarTerritorios(&qtdTerritorios);

    int opcao;
    do {
        printf("\n===== MENU DE AÇÕES =====\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar territorio\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirMapa(mapa, qtdTerritorios);
                break;
            case 2: {
                int atq, def;

                exibirMapa(mapa, qtdTerritorios);
                printf("\nEscolha o numero do territorio atacante: ");
                scanf("%d", &atq);
                getchar();

                printf("Escolha o numero do territorio defensor: ");
                scanf("%d", &def);
                getchar();

                if (atq < 1 || atq > qtdTerritorios || def < 1 || def > qtdTerritorios) {
                    printf("❌ Territorio invalido!\n");
                    break;
                }

                if (strcmp(mapa[atq - 1].cor, mapa[def - 1].cor) == 0) {
                    printf("⚠️  Voce nao pode atacar um territorio da mesma cor!\n");
                    break;
                }

                atacar(&mapa[atq - 1], &mapa[def - 1]);
                break;
            }
            case 3:
                printf("\nEncerrando o jogo... Até a próxima batalha!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);

    liberarMemoria(mapa);
    return 0;
}

// ------------------ FUNÇÕES AUXILIARES ------------------

// Cadastra os territórios dinamicamente
Territorio* cadastrarTerritorios(int* qtd) {
    Territorio* mapa = (Territorio*) calloc(*qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    printf("\n=== CADASTRO DE TERRITORIOS ===\n\n");
    for (int i = 0; i < *qtd; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exercito (ex: Azul, Verde): ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("----------------------------------\n");
    }

    return mapa;
}

// Exibe todos os territórios
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("⚠️  O territorio atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtq = (rand() % 6) + 1; // valor entre 1 e 6
    int dadoDef = (rand() % 6) + 1;

    printf("\n🎲 Rolando os dados...\n");
    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtq);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDef);

    if (dadoAtq >= dadoDef) {
        printf("🔥 O atacante venceu a batalha!\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("🏴 Territorio conquistado! %s agora pertence ao exercito %s.\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2; // metade das tropas migram
            atacante->tropas = atacante->tropas / 2; // metade fica
        }
    } else {
        printf("🛡️  O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }

    printf("\n--- Situação após a batalha ---\n");
    printf("%s -> Tropas: %d | Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s -> Tropas: %d | Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}

// Libera a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}
