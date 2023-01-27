#include "../graph.c"
#include <limits.h>

int **adj_list_to_adj_matrix(graph *graph) {
    int i, j;
    node *current;

    int **adj_matrix = (int **)malloc(graph->vertex_list_size * sizeof(int *));
    for (i = 0; i < graph->vertex_list_size; i++)
        adj_matrix[i] = (int *)malloc(graph->vertex_list_size * sizeof(int));

    for (i = 0; i < graph->vertex_list_size; i++) {
        for (j = 0; j < graph->vertex_list_size; j++) {
            adj_matrix[i][j] = 0;
        }
    }

    for (i = 0; i < graph->vertex_list_size; i++) {
        current = graph->vertex_list[i]->adj_list;
        while (current != NULL) {
            for (j = 0; j < graph->vertex_list_size; j++) {
                if (graph->vertex_list[i]->id == current->source && graph->vertex_list[j]->id == current->destiny) {
                    adj_matrix[i][j] = current->weight;
                }
            }
            current = current->next;
        }
    }

    return adj_matrix;
}

void warshall(graph *graph) {
    int i, j, k;
    node *current;
    int v = graph->vertex_list_size;
    int **adj_matrix = adj_list_to_adj_matrix(graph);
    int **dist = adj_matrix;

    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            printf(" %d ", dist[i][j]);
            if(dist[i][j] == 0 && i != j)
            dist[i][j] = INT_MAX;
            else if(i == j){
                dist[i][j] = 0;
            }
            
        }
        printf("\n");
    }

    for (k = 0; k < v; k++) {
        // Escolhe todos os vertices como origem um por um
        for (i = 0; i < v; i++) {
            // Escolhe todos os vertices como destino 
            //para o vertice escolhido como origem
            for (j = 0; j < v; j++) {
                // Se o vertice k está no menor caminho de i para j
                // então atualiza o valor de dist[i][j]
               if(dist[i][k] + dist[k][j] < dist[i][j] && dist[i][j] != 0 && dist[i][k] != INT_MAX
               && dist[k][j] != INT_MAX){
                    dist[i][j] = dist[i][k] + dist[k][j];
                
               }
            }
        }
    }

    // 0 3 4 7
    // 13 0 17 5
    // 11 14 0 3
    // 8 11 12 0
    printf("\n-------------------------------------\n");

    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            if(dist[i][j] < 0){
                printf("O grafo possui ciclos negativos! \n");
                return;
            }
        }
    }
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            if(dist[i][j] != INT_MAX){
                printf("%d ", dist[i][j]);
            }
            else if(dist[i][j] == INT_MAX){
                printf("X ");
            }
        }
        printf("\n");
    }
}




int main(){
    graph *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 5 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false, 2);
    insert_edge(&list1, 1, 2, false, 6);
    insert_edge(&list1, 2, 1, false, 7);
    insert_edge(&list1, 3, 2, false, 1);
    insert_edge(&list1, 3, 4, false, 3);
    insert_edge(&list1, 4, 0, false, 1);
    insert_edge(&list1, 4, 1, false, 4);

    show_graph(list1);
    printf("====================================\n");
    printf("---------- WARSHALL -----------\n");
    warshall(list1);

    return 0;
}