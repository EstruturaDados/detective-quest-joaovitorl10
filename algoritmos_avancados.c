#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para cada sala da mansão
typedef struct Sala {
    char nome[50];
    char pista[100]; // Pista opcional
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura para nó da BST de pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Cria dinamicamente uma sala
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    if (pista)
        strcpy(novaSala->pista, pista);
    else
        novaSala->pista[0] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Insere uma pista na BST
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (!raiz) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    // Se igual, não insere duplicado
    return raiz;
}

// Exibe pistas em ordem alfabética
void exibirPistas(PistaNode* raiz) {
    if (!raiz) return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// Explora as salas e coleta pistas
void explorarSalasComPistas(Sala* atual, PistaNode** pistas) {
    char opcao;
    while (atual) {
        printf("\nVocê está em: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
        } else {
            printf("Nenhuma pista neste cômodo.\n");
        }
        printf("Opções: [e] Esquerda | [d] Direita | [s] Sair\nEscolha: ");
        scanf(" %c", &opcao);
        if (opcao == 'e')
            atual = atual->esquerda;
        else if (opcao == 'd')
            atual = atual->direita;
        else if (opcao == 's')
            break;
        else
            printf("Opção inválida!\n");
    }
}

// Libera memória da árvore de salas
void liberarSalas(Sala* raiz) {
    if (!raiz) return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// Libera memória da BST de pistas
void liberarPistas(PistaNode* raiz) {
    if (!raiz) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

int main() {
    // Monta o mapa fixo da mansão
    Sala* hall = criarSala("Hall de Entrada", "Chave misteriosa");
    hall->esquerda = criarSala("Sala de Estar", "Pegada de lama");
    hall->direita = criarSala("Cozinha", "Copo quebrado");
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro rasgado");
    hall->esquerda->direita = criarSala("Jardim", NULL);
    hall->direita->esquerda = criarSala("Despensa", "Porta secreta");
    hall->direita->direita = criarSala("Quarto", "Perfume estranho");

    PistaNode* pistas = NULL;

    printf("Bem-vindo ao Detective Quest!\nExplore a mansão e colete pistas.\n");
    explorarSalasComPistas(hall, &pistas);

    printf("\nPistas coletadas (ordem alfabética):\n");
    exibirPistas(pistas);

    liberarSalas(hall);
    liberarPistas(pistas);
    return 0;
}
