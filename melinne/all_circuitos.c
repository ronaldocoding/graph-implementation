// Adjascency List representation in C

#include <stdio.h>
#include <stdlib.h>
#include "../graph.c"

void print_circuit(int *stack, int top){
    int i;
    printf("foi print");
    for(i = top; i >= 0; i--){
        printf("%d ", stack[i]);
    }
}

void find_circuits_util(vertex_list *Graph, int vertex, int *stack, int *top, int *visited){
    int n_vertices = Graph->vertex_list_size;
    visited[vertex] = 1;
    stack[++(*top)] = vertex;

    node * current_node = Graph->vertex_list[vertex]->adj_list;
    printf("foi util");
    while(current_node != NULL){
        printf(" (%d) ", Graph->vertex_list[vertex]->id);
        printf("- whi %d ", current_node->destiny);
        int u = current_node->destiny;
        if(visited[u] == 0){

            find_circuits_util(Graph, u, stack, top, visited);
        }
        else if(*top > 0 && stack[*top] == u){
            print_circuit(stack, *top);
        }
        current_node = current_node->next;
    }

    visited[vertex] = 0;
    (*top)--;
    printf(" | util end.");
    
}

void find_circuits(vertex_list *Graph){
    int n_vertices = Graph->vertex_list_size;
    int *stack = (int *)malloc(sizeof(int) * n_vertices);
    int top = -1;
    int i;
    int visited[n_vertices];
    for(i = 0; i < n_vertices; i++){
        if(!visited[i]){
            find_circuits_util(Graph, i, stack, &top, visited);
        }
    }

    free(stack);
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

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 1 
     * de peso 10
    */ 
    insert_edge(&list1, 0, 1, false, 10);
 
    insert_edge(&list1, 0, 2, false, 1);

    insert_edge(&list1, 3, 0, false, 5);

    insert_edge(&list1, 1, 3, false, 5);

    insert_edge(&list1, 1, 4, false, 12);

    insert_edge(&list1, 2, 3, false, 8);

    insert_edge(&list1, 3, 4, false, -18);


    printf("=================\n");
    // Mostra o grafo
    show_graph(list1);
    
    printf("=================\n");
    
    
    find_circuits(list1);
    
}