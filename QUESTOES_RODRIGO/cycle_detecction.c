#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int numVertices, numArestas;
int listaAdj[MAX_VERTICES][MAX_VERTICES]; // matriz de adjacência simples (pode ser lista também)
int grauAdj[MAX_VERTICES];

// Cores para DFS:
// 0 = não visitado
// 1 = visitando (está na pilha de recursão)
// 2 = visitado completamente
int cor[MAX_VERTICES];

int temCiclo;

// DFS para detectar ciclo
void dfs(int u) {
    cor[u] = 1; // visitando
    for (int i = 0; i < grauAdj[u]; i++) {
        int v = listaAdj[u][i];
        if (cor[v] == 0) {
            dfs(v);
            if (temCiclo) return; // já encontrou ciclo, pode parar
        } else if (cor[v] == 1) {
            // encontrou um vértice que está na pilha de recursão -> ciclo
            temCiclo = 1;
            return;
        }
    }
    cor[u] = 2; // visitado completamente
}

int main() {
    scanf("%d %d", &numVertices, &numArestas);

   // Inicializando tudo: graus, a lista de adjacências, as cores, e depois rodando o DFS pra achar ciclo
    for (int i = 0; i < numVertices; i++) {
        grauAdj[i] = 0;
    }
 
    for (int i = 0; i < numArestas; i++) {
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        listaAdj[origem][grauAdj[origem]++] = destino;
    }

    for (int i = 0; i < numVertices; i++) {
        cor[i] = 0;
    }
    temCiclo = 0;

    for (int i = 0; i < numVertices; i++) {
        if (cor[i] == 0) {
            dfs(i);
            if (temCiclo) break;
        }
    }

    printf("%d\n", temCiclo);

    return 0;
}