#include "../graph.c"
#include <limits.h>
/**
 * Bellman_Ford(G,pesos,inicial)
    para todo vertice ∈ V
        λ[vertice] ← ∞
        π[vertice] ← nulo

    λ[inicial] ← 0

    para i de 1 até |V| -1
        para toda aresta = (u,v) ∈ A
            se λ[v] > λ[u] + pesos(u,v) # relaxamento
               λ[v] ← λ[u] + pesos(u,v)
               π[v] ← u
 */


bool Bellman_Ford(vertex_list **Graph, int source_id){
  
    int n_vertices = (*Graph)->vertex_list_size;
    int E = 0;
    // Inicializa as distancias do vertice fonte para todos os vertices como infinito
    int dist[n_vertices];
    for(int i = 0; i < n_vertices;i++){
        dist[i] = INT_MAX;
    }
    dist[source_id] = 0;
    // Relaxa todos as arestas |V| - 1 vezes.
    for(int i = 1; i <= n_vertices; i++){
        for(int j = 0; j < n_vertices; j++){
            struct node *temp = (*Graph)->vertex_list[j]->adj_list;
            while(temp){
                int u = j;
                int v = temp->destiny;
                int weight = temp->weight;
                if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                }
                temp = temp->next;                
                E++;
            }
        }
    }

    printf("\n---------------- BELLMAN-FORD---------------\n");
    printf("Partindo do vertice %d... \n", source_id);
    // Executa a etapa de relaxamento mais uma vez
    for(int i = 1; i <= n_vertices; i++){
        for(int j = 0; j < n_vertices; j++){
            struct node *temp = (*Graph)->vertex_list[j]->adj_list;
            while(temp){
                int u = j;
                int v = temp->destiny;
                int weight = temp->weight;
                if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                    printf("\n O grafo possui arestas com peso negativo!\n\n");
                    return false;
                }

                temp = temp->next;
            } 
        }
    }
    for(int k = 0; k < n_vertices; k++){
        if(k != source_id && dist[k] < INT_MAX){
            printf("A menor distancia do vertice (%d) para o vertice (%d) == %d\n",
            source_id, k, dist[k]);
        }
    }

    return true;
}

int main()
{
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
     
    Bellman_Ford(&list1, 0);
}
