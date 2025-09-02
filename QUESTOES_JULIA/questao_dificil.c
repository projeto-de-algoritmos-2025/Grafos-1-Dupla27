#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG 18
#define MAXSIZE 100005
#define INF 0x3f3f3f3fLLU

typedef long long ll;

// Estruturas
typedef struct No {
    int u, w;
    struct No *prox;
} No;

typedef struct Grafo {
    No *adj;
} Grafo;

// Variáveis
int n;
ll dist[MAXSIZE];
int depth[MAXSIZE];
int parent[MAXSIZE][LOG];

// Grafo e lista de adjacência
Grafo* criarGrafo(int tamanho) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->adj = (No*) malloc(sizeof(No) * (tamanho + 1));
    for (int i = 0; i <= tamanho; i++) {
        g->adj[i].prox = NULL;
    }
    return g;
}

No* criarNo(int u, int w) {
    No *novo = (No*) malloc(sizeof(No));
    novo->u = u;
    novo->w = w;
    novo->prox = NULL;
    return novo;
}

void adicionarAresta(Grafo *g, int u, int v, int w) {
    No *novo = criarNo(u, w);
    novo->prox = g->adj[v].prox;
    g->adj[v].prox = novo;
}

// Calcular profundidade, distância e pais
void dfs(int s, Grafo *g) {
    for (No *i = g->adj[s].prox; i != NULL; i = i->prox) {
        int v = i->u;
        int w = i->w;
        if (depth[v] == INF) {
            depth[v] = depth[s] + 1;
            dist[v] = dist[s] + (ll)w;
            parent[v][0] = s;
            dfs(v, g);
        }
    }
}

// Pré processamento
void preprocessar() {
    for (int i = 1; i < LOG; i++) {
        for (int u = 0; u < n; u++) {
            if (parent[u][i - 1] != -1) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
        }
    }
}

// Encontra o LCA 
int LCA(int u, int v) {
    if (depth[u] > depth[v]) {
        int tmp = u; u = v; v = tmp;
    }

    int diff = depth[v] - depth[u];
    for (int i = 0; i < LOG; i++) {
        if ((diff >> i) & 1) {
            v = parent[v][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

// Principal
int main() {
    int u, v, w, q;

    while (scanf("%d%*c", &n), n) {
        Grafo *g = criarGrafo(n + 1);

        // Lendo arestas
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &v, &w);
            if (i < v) adicionarAresta(g, v, i, w);
            else adicionarAresta(g, i, v, w);
        }

        // Iniciando distâncias e profundidades
        for (int i = 0; i <= n; i++) {
            dist[i] = INF;
            depth[i] = INF;
            for (int j = 0; j < LOG; j++) parent[i][j] = -1;
        }

        // Raiz = 0
        dist[0] = 0;
        depth[0] = 0;
        parent[0][0] = 0;

        // Executa DFS e pré processamento
        dfs(0, g);
        preprocessar();

        // Consulta
        scanf("%d", &q);
        while (q--) {
            scanf("%d %d", &u, &v);
            int lca = LCA(u, v);
            ll ans = (dist[u] - dist[lca]) + (dist[v] - dist[lca]);
            printf("%lld%c", ans, q > 0 ? ' ' : '\n');
        }
    }

    return 0;
}
