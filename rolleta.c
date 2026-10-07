#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Casa {
    int numero;
    struct Casa *prox, *ant;
} Casa;

// Cria uma lista duplamente encadeada circular 
Casa *criar_roleta(int n) {
    Casa *inicio = NULL, *fim = NULL;
    for (int i = 0; i < n; i++) {
        Casa *novo = malloc(sizeof(Casa));
        novo->numero = i;
        if (inicio == NULL) {
            inicio = fim = novo;
        } else {
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        }
    }
    fim->prox = inicio;   // fecha o círculo
    inicio->ant = fim;
    return inicio;
}

int main(void) {
    srand(time(NULL));
    Casa *bolinha = criar_roleta(37);
    int pontos = 0, escolha;
    char outra;

    printf("=== Roleta Carioca ===\n");
    do {
        printf("Escolha um numero (0-36): ");
        scanf("%d", &escolha);

        int impulso = rand() % 100 + 37;      // força do giro
        for (int i = 0; i < impulso; i++)
            bolinha = bolinha->prox;          // a bolinha percorre a roleta

        printf("A bolinha parou no %d\n", bolinha->numero);
        if (bolinha->numero == escolha) {
            pontos++;
            printf("Acertou! Pontos: %d\n", pontos);
        } else {
            printf("Errou. Pontos: %d\n", pontos);
        }

        printf("Jogar de novo? (s/n): ");
        scanf(" %c", &outra);
    } while (outra == 's');

    // libera a memória: quebra o círculo e percorre até o fim
    Casa *fim = bolinha->ant;
    fim->prox = NULL;
    while (bolinha != NULL) {
        Casa *prox = bolinha->prox;
        free(bolinha);
        bolinha = prox;
    }
    return 0;
}
