#include "../graph.c"


void kahn(graph *graph)
{
    int v = graph->vertex_list_size;
    int in_degree[v];
    int i;
    for (i = 0; i < v; i++)
        in_degree[i] = 0;

    // Percorre a lista de adjacência para preencher o grau de cada vertice
    for (i = 0; i < v; i++)
    {
        struct node *temp = graph->vertex_list[i]->adj_list;
        while (temp)
        {
            int index = temp->destiny;
            in_degree[index]++;
            temp = temp->next;
        }
    }

    // Create a queue and enqueue all vertices with in_degree 0
    // Cria uma "fila" e enfileira todos os vertices em que o grau de entrada é zero, ou seja, não possui nenhuma aresta que leva até ele
    int queue[v];
    int front = 0, rear = -1;
    for (i = 0; i < v; i++)
        if (!in_degree[i])
            queue[++rear] = i;

    // Contador para vertices visitados
    int count = 0;

    // Cria um vetor para armazenar o resultado (uma ordenação topológica dos vértices)
    int top_order[v];

    while (front <= rear)
    {
        // Desenfileira um vertice da fila
        int u = queue[front++];
        top_order[count++] = u;

        // Itera por todos os vértices adjacentes do vértice desenfileirado e diminui seu grau de entrada
        // Faça isso até o grau de entrada se tornar zero e adicione na fila
        struct node *temp = graph->vertex_list[u]->adj_list;
        while (temp)
        {
            if (!(--in_degree[temp->destiny]))
                queue[++rear] = temp->destiny;
            temp = temp->next;
        }
    }

    if (count != v)
    {
        printf("O grafo possui ciclos\n");
        return;
    }

    printf("------- ORDEM TOPOLOGICA COM KAHN ------\n");
    // Print a ordenação topologica
    for (i = 0; i < v; i++)
        printf("%d ", top_order[i]);
}

int main()
{
    graph *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 5 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false, 5);

    insert_edge(&list1, 0, 2, false, 1);

    insert_edge(&list1, 0, 3, false, 1);

    insert_edge(&list1, 0, 4, false, 5);

    insert_edge(&list1, 2, 3, false, 5);

    insert_edge(&list1, 3, 1, false, 5);

    insert_edge(&list1, 4, 1, false, 5);

    insert_edge(&list1, 4, 2, false, 5);

    insert_edge(&list1, 4, 3, false, 5);

    insert_edge(&list1, 5, 3, false, 5);

    insert_edge(&list1, 6, 4, false, 5);

    insert_edge(&list1, 6, 7, false, 5);

    insert_edge(&list1, 7, 2, false, 5);

    printf("=================\n");
    // Mostra o grafo
    show_graph(list1);

    printf("=================\n");

    kahn(list1);
}
