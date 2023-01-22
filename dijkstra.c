#include <stdio.h>
#include <stdlib.h>

/*------- Definições -------- */

#define INFTY 1000000
#define NIL -1
#define TRUE 1
#define FALSE 0

/*------- Estruturas -------- */

/*Lista encadeada para guardar os vizinhos de cada nó.*/
typedef struct node
{
    int id; /*identificação do vértice*/
    struct node *proximo;
} Node;

typedef struct graph
{
    int V;           /*Número de vértices no Grafo.*/
    int E;           /*Número de arestas no Grafo.*/
    Node **listadj;  /*Lista de adjacências.*/
    int **matrixadj; /*Matriz de adjacências.*/
} Graph;

typedef struct queue
{
    int tam;
    int *elems;
} Queue;

/*------- Funções -------- */

Graph *init_graph(int V);
void adicionar_aresta(Graph *G, int u, int v, int w);
int **inicializa_matriz_de_adjacencias(int r, int c, int w);
Node *criar_vertice(int v, Node *lista);
Queue *criar_queue(int tam);
int vazio_queue(Queue *Q);
int extract_min(Queue *Q, int dist[], int V);
void initialize_single_source(int source, int pai[], int dist[], Queue *Q, int V);
void relax(int u, int v, Graph *G, int pai[], int dist[]);
void Dijkstra(Graph *G, int source);
void BellmanFord(Graph *G, int source);
int FloydWarshall(Graph *G);

/*------------------------*/

/* A função abaixoc cria um Grafo e inicializa seus atributos. */
/* Também são criadas listas de adjancência vazias para cada um dos vértices. */
Graph *init_graph(int V)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V;
    G->E = 0;
    G->listadj = (Node **)malloc(V * sizeof(Node *));
    int v;
    for (v = 0; v < V; v++)
        G->listadj[v] = NULL;
    G->matrixadj = inicializa_matriz_de_adjacencias(V, V, INFTY);
    return G;
}

/*Alocando memória e inicializando com {val} a matriz de adjacência do Grafo: */
int **inicializa_matriz_de_adjacencias(int r, int c, int w)
{
    int i, j;
    int **mat = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        mat[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            mat[i][j] = w;
    return mat;
}

/* A função abaixo insere uma aresta {u-v} no Grafo {G} com peso {w}.
Se o Grafo já tem a aresta então nada é feito. */
void adicionar_aresta(Graph *G, int u, int v, int w)
{

    Node *aux; /*Variável para percorrer a lista de adjacência do vértice {u}*/

    for (aux = G->listadj[u]; aux != NULL; aux = aux->proximo)
        if (aux->id == v)
            return;
    G->listadj[u] = criar_vertice(v, G->listadj[u]);

    /*Adiciona a aresta na matriz de adjacência: */
    G->matrixadj[u][v] = w;
    G->E++; /*Incrementa o número de arestas no Grafo.*/
}

/*A função abaixo aloca um novo nó {v} na lista encadeada {lista}.*/
Node *criar_vertice(int v, Node *lista)
{
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->id = v;
    novo->proximo = lista;
    return novo;
}

/*Função para inicializar uma fila: */
Queue *criar_queue(int tam)
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->tam = tam;
    Q->elems = (int *)malloc(tam * sizeof(int));
    return Q;
}

int vazio_queue(Queue *Q)
{
    return (Q->tam == 0);
}

/*Esta função extrai o vértice com menor custo de uma fila Q: */
int extract_min(Queue *Q, int dist[], int V)
{
    int min = INFTY, min_index;
    int v;
    for (v = 0; v < V; v++)
    {
        if ((Q->elems[v] == FALSE) && (dist[v] < min))
        {
            min = dist[v];
            min_index = v;
        }
    }
    Q->elems[min_index] = TRUE;
    Q->tam--;
    return min_index;
}

/*Esta função inicializa os vértices em uma busca por caminhos mínimos: */
void initialize_single_source(int source, int pai[], int dist[], Queue *Q, int V)
{
    int v;
    for (v = 0; v < V; v++)
    {
        pai[v] = NIL;
        dist[v] = INFTY;
        Q->elems[v] = FALSE;
    }
    dist[source] = 0;
}

/*Função para relaxação de arestas: */
void relax(int u, int v, Graph *G, int pai[], int dist[])
{
    if (dist[v] > dist[u] + G->matrixadj[u][v])
    {
        dist[v] = dist[u] + G->matrixadj[u][v];
        pai[v] = u;
    }
}

/*Caminhos mínimos por Dijkstra: */
void Dijkstra(Graph *G, int source)
{

    int pai[G->V];  /*Árvore de caminhos mínimos.*/
    int dist[G->V]; /*Distâncias mínimas.*/
    Queue *Q = criar_queue(G->V);

    initialize_single_source(source, pai, dist, Q, G->V);

    while (!vazio_queue(Q))
    {
        int u = extract_min(Q, dist, G->V);
        Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
        for (v = G->listadj[u]; v != NULL; v = v->proximo)
        {
            relax(u, v->id, G, pai, dist);
        }
        printf("Nó = %d (predecessor = %d), caminho mínimo do nó %d até o nó %d = %d\n", u, pai[u], source, u, dist[u]);
    }
}

int main()
{

    int algoritmo = 0;

    /*Dijkstra*/
    if (algoritmo == 0)
    {
        /* Posição dos vértices (slide 24): */
        /*                                  */
        /*            1       2             */
        /*       0                3         */
        /*            5       4             */
        /*                                  */

        /*Número de vértices: */
        int V = 6;

        /*Inicializando o Grafo direcionado G: */
        Graph *G = init_graph(V);

        /*Adicionando as arestas:*/
        adicionar_aresta(G, 0, 1, 10);
        adicionar_aresta(G, 1, 2, 1);
        adicionar_aresta(G, 2, 3, 2);
        adicionar_aresta(G, 4, 3, 5);
        adicionar_aresta(G, 4, 2, 6);
        adicionar_aresta(G, 2, 4, 4);
        adicionar_aresta(G, 5, 2, 9);
        adicionar_aresta(G, 5, 1, 3);
        adicionar_aresta(G, 1, 5, 2);
        adicionar_aresta(G, 0, 5, 5);
        adicionar_aresta(G, 4, 0, 7);
        adicionar_aresta(G, 5, 4, 2);

        /*Caminhos mínimos por Dijkstra: */
        int source = 0;
        Dijkstra(G, source);
    }

    return 0;
}