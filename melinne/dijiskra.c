#include "../graph.c"
#include <limits.h>
#include <stdbool.h>

void dijkstra(vertex_list **Graph, int start)
{
    int distance[(*Graph)->vertex_list_size];
    int visited[(*Graph)->vertex_list_size];

    // Inicializa a distancia de todos os vertices para INFINITO e os vertices visitados
    for (int i = 0; i < (*Graph)->vertex_list_size; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Muda o valor da distancia do vertice inicial para 0
    distance[start] = 0;

    // Encontra o caminho mais curto para todos os vertices
    for (int i = 0; i < (*Graph)->vertex_list_size - 1; i++)
    {
        // Escolha o vértice de distância mínima do conjunto de vértices ainda não visitados
        int min = INT_MAX, min_index;
        for (int j = 0; j < (*Graph)->vertex_list_size; j++)
        {
            if (!visited[j] && distance[j] <= min)
            {
                min = distance[j];
                min_index = j;
            }
        }
        // Marca o vértice escolhido como visitado
        visited[min_index] = 1;
        // Atualiza os valores de distância dos vértices adjacentes do vértice escolhido
        node *temp = (*Graph)->vertex_list[min_index]->adj_list;
        while (temp != NULL)
        {
            if (!visited[temp->destiny] && distance[min_index] != INT_MAX 
            && distance[min_index] + temp->weight < distance[temp->destiny])
            {
                distance[temp->destiny] = distance[min_index] + temp->weight;
            }
            temp = temp->next;
        }
    }
    printf("\n---------------- DIJKSTRA ---------------\n");
    // Imprime o menor caminho do vertice de inicio para todos os outros vertices
    printf("Vetice \tdistancia de (%d)\n", start);
    for (int i = 0; i < (*Graph)->vertex_list_size; i++)
    {
        if(i != start && distance[i] < INT_MAX){
        printf("%d\t%d\n", i, distance[i]);
        }
    }
}

int main(){
    vertex_list *list1 = NULL;

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

    insert_edge(&list1, 0, 1, true, 10); 
    insert_edge(&list1, 0, 2, true, 1);
    insert_edge(&list1, 0, 3, true, 20);
    insert_edge(&list1, 1, 3, true, 5);
    insert_edge(&list1, 1, 4, true, 12);
    insert_edge(&list1, 2, 3, true, 8);
    insert_edge(&list1, 3, 4, true, 18);
    printf("====================== GRAFO ===================\n");
    // Mostra o grafo
    show_graph(list1);  
    printf("==============================================\n");
    dijkstra(&list1, 0);
}