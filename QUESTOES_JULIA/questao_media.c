#include <stdio.h>
#include <stdlib.h>

// Definindo nó
typedef struct No {
    int chave;
    struct No *esq, *dir;
} No;

//  Encontra o pai para inserir um novo nó
No* encontrarPai(No *raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor <= raiz->chave) {
        if (raiz->esq == NULL) 
            return raiz;
        else 
            return encontrarPai(raiz->esq, valor);
    } else {
        if (raiz->dir == NULL) 
            return raiz;
        else 
            return encontrarPai(raiz->dir, valor);
    }
}

// Percursos
void percursoPreOrdem(No *raiz) {
    if (raiz != NULL) {
        printf(" %d", raiz->chave);
        percursoPreOrdem(raiz->esq);
        percursoPreOrdem(raiz->dir);
    }
}

void percursoInOrdem(No *raiz) {
    if (raiz != NULL) {
        percursoInOrdem(raiz->esq);
        printf(" %d", raiz->chave);
        percursoInOrdem(raiz->dir);
    }
}

void percursoPosOrdem(No *raiz) {
    if (raiz != NULL) {
        percursoPosOrdem(raiz->esq);
        percursoPosOrdem(raiz->dir);
        printf(" %d", raiz->chave);
    }
}

// Principal
int main() {
    int casos, n, i, valor;
    No *raiz, *novo, *pai;

    scanf("%d", &casos);

    for (int c = 1; c <= casos; c++) {
        raiz = NULL;
        scanf("%d", &n);

        for (i = 0; i < n; i++) {
            scanf("%d", &valor);

            novo = (No*) malloc(sizeof(No));
            novo->chave = valor;
            novo->esq = novo->dir = NULL;

            pai = encontrarPai(raiz, valor);
            if (pai == NULL) {
                raiz = novo; // primeiro nó
            } else if (valor <= pai->chave) {
                pai->esq = novo;
            } else {
                pai->dir = novo;
            }
        }

        printf("Case %d:", c);

        printf("\nPre.:");
        percursoPreOrdem(raiz);

        printf("\nIn..:");
        percursoInOrdem(raiz);

        printf("\nPost:");
        percursoPosOrdem(raiz);

        printf("\n\n");
    }

    return 0;
}
