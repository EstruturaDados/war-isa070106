#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===============================================
// Estrutura que representa um território no jogo
// ===============================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ====================================================
// Função: exibirMapa
// Exibe o estado atual de todos os territórios no mapa
// ====================================================
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s (Exercito: %s , Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==========================================\n");
}

// ===================================================================
// Função: atribuirMissao
// Sorteia aleatoriamente uma missão e copia para o destino do jogador
// ===================================================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// ==========================================================
// Função: atacar
// Simula um ataque entre dois territórios com base em rolagem
// de dados (valores de 1 a 6). Atualiza cor e tropas conforme resultado.
// ==========================================================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNao e possivel atacar um territorio aliado!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Ataque bem-sucedido! O territorio %s foi conquistado!\n", defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Ataque falhou! O exercito atacante perdeu uma tropa.\n");
        atacante->tropas--;
    }
}

// ================================================================
// Função: verificarMissao
// Checa se a missão atual do jogador foi cumprida (verificação simples)
// ================================================================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de lógica simples:
    // "Destruir o exercito Verde" = nenhum território pode ser Verde
    if (strstr(missao, "Verde") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0)
                return 0; // ainda há exércitos verdes
        }
        return 1; // missão cumprida
    }
    // Caso queira expandir, pode adicionar mais regras aqui
    return 0;
}

// ================================================================
// Função: liberarMemoria
// Libera toda a memória alocada dinamicamente
// ================================================================
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// ========================
// Função principal (main)
// ========================
int main() {
    srand(time(NULL));

    int totalTerritorios = 5;

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    // Definição dos territórios e cores iniciais
    strcpy(mapa[0].nome, "America"); strcpy(mapa[0].cor, "Verde"); mapa[0].tropas = 5;
    strcpy(mapa[1].nome, "Europa"); strcpy(mapa[1].cor, "Azul"); mapa[1].tropas = 3;
    strcpy(mapa[2].nome, "Asia"); strcpy(mapa[2].cor, "Vermelho"); mapa[2].tropas = 2;
    strcpy(mapa[3].nome, "Africa"); strcpy(mapa[3].cor, "Amarelo"); mapa[3].tropas = 4;
    strcpy(mapa[4].nome, "Oceania"); strcpy(mapa[4].cor, "Branco"); mapa[4].tropas = 1;

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos.",
        "Destruir o exercito Verde.",
        "Ocupar America e Africa simultaneamente.",
        "Eliminar todas as tropas Vermelhas.",
        "Controlar 4 territorios diferentes."
    };

    // Missão do jogador
    char* missao = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missao, missoes, 5);

    printf("\n");
    exibirMapa(mapa, totalTerritorios);

    // Exibe a missão uma única vez no início
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");
    printf("%s\n", missao);

    int opcao;
    do {
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int atacante, defensor;
            printf("\nEscolha o territorio atacante (1 a %d): ", totalTerritorios);
            scanf("%d", &atacante);
            printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
            scanf("%d", &defensor);

            if (atacante < 1 || atacante > totalTerritorios ||
                defensor < 1 || defensor > totalTerritorios) {
                printf("Escolha invalida!\n");
                continue;
            }

            atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

            if (verificarMissao(missao, mapa, totalTerritorios)) {
                printf("\n*** MISSAO CUMPRIDA! ***\n");
                printf("O Exercito Azul venceu o jogo!\n");
                break;
            }
        }
        else if (opcao == 2) {
            printf("\n--- SUA MISSAO ---\n%s\n", missao);
        }

        exibirMapa(mapa, totalTerritorios);

    } while (opcao != 0);

    liberarMemoria(mapa, missao);
    printf("\nJogo encerrado.\n");

    return 0;
}
