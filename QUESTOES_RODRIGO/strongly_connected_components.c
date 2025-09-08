// Anotações

// 1. Verificar se o grafo é fortemente conectado - dado quaisquer
// dois nós, eles são MUTUALMENTE atingíveis

// 2. A entrada é dada da seguinte forma:
// Linha 1: número de nós (0 até V-1) e número de arestas
// Linha 2-Q: nó fonte e nó alvo
// Linha Q- u(q-1) e v(q-1): pares de nós do grafo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 10000 //por causa do limite da entrada

int numVertices, numArestas, numConsultas;
int componente[MAXV];
int visitado[MAXV];
int ordemTopo[MAXV], tamanhoOrdemTopo = 0;

int *listaAdj[MAXV], *listaAdjTransposta[MAXV];
int grauAdj[MAXV], grauAdjTransposta[MAXV];

// Antes de inverter o grafo, permitindo guardá-lo numa pilha para entender a ordem topoológica
void dfsOriginal(int u) {
    visitado[u] = 1;
    for (int i = 0; i < grauAdj[u]; i++) {
        int v = listaAdj[u][i];
        if (!visitado[v]) {
            dfsOriginal(v);
        }
    }
    ordemTopo[tamanhoOrdemTopo++] = u;
}

// Após inverter o grafo, pegando a ordem inversa para identificar aonde há componentes fortemente conectados
void dfsTransposto(int u, int idComponente) {
    componente[u] = idComponente;
    for (int i = 0; i < grauAdjTransposta[u]; i++) {
        int v = listaAdjTransposta[u][i];
        if (componente[v] == -1) {
            dfsTransposto(v, idComponente);
        }
    }
}

int main() {
    scanf("%d %d", &numVertices, &numArestas);

    // Inicializa graus das listas de adjacência
    memset(grauAdj, 0, sizeof(int) * numVertices);
    memset(grauAdjTransposta, 0, sizeof(int) * numVertices);

    int origem, destino;

    // Primeiro passo: contar o número de adjacentes para alocar os vetores
    // Salvamos as arestas para ler duas vezes, pois precisamos alocar as listas antes de preencher
    int *arestasOrigem = malloc(sizeof(int) * numArestas);
    int *arestasDestino = malloc(sizeof(int) * numArestas);

    for (int i = 0; i < numArestas; i++) {
        scanf("%d %d", &origem, &destino);
        arestasOrigem[i] = origem;
        arestasDestino[i] = destino;
        grauAdj[origem]++;
        grauAdjTransposta[destino]++;
    }

    // Criando a lista de adjacências
    for (int i = 0; i < numVertices; i++) {
        listaAdj[i] = malloc(sizeof(int) * grauAdj[i]);
        listaAdjTransposta[i] = malloc(sizeof(int) * grauAdjTransposta[i]);
    }

    // Resetar contadores para preenchimento
    memset(grauAdj, 0, sizeof(int) * numVertices);
    memset(grauAdjTransposta, 0, sizeof(int) * numVertices);

    // Preencher as listas de adjacência
    for (int i = 0; i < numArestas; i++) {
        origem = arestasOrigem[i];
        destino = arestasDestino[i];
        listaAdj[origem][grauAdj[origem]++] = destino;
        listaAdjTransposta[destino][grauAdjTransposta[destino]++] = origem;
    }

    free(arestasOrigem);
    free(arestasDestino);

    // Rodar o primeiro DFS para definir a ordem topológica
    memset(visitado, 0, sizeof(int) * numVertices);
    tamanhoOrdemTopo = 0;
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            dfsOriginal(i);
        }
    }

    // Rodar o segundo DFS no grafo transposto para identificar componentes
    for (int i = 0; i < numVertices; i++) {
        componente[i] = -1;
    }
    int idComponente = 0;
    for (int i = tamanhoOrdemTopo - 1; i >= 0; i--) {
        int u = ordemTopo[i];
        if (componente[u] == -1) {
            dfsTransposto(u, idComponente++);
        }
    }

    // Ler número de consultas
    scanf("%d", &numConsultas);

    // Responder consultas verificando se pertencem à mesma componente
    for (int i = 0; i < numConsultas; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", (componente[u] == componente[v]) ? 1 : 0);
    }

    // Liberar memória alocada
    for (int i = 0; i < numVertices; i++) {
        free(listaAdj[i]);
        free(listaAdjTransposta[i]);
    }

    return 0;
}
