#include "../graph.c"

void findCircuits(graph *graph) {
    for (int i = 0; i < graph->vertex_list_size; i++) {
        graph->vertex_list[i]->visited = false;
    }

    for (int i = 0; i < graph->vertex_list_size; i++) {
        if (!graph->vertex_list[i]->visited) {
            dfs(graph->vertex_list[i]);
        }
    }
}

void dfs(vertex *v) {
    v->visited = true;
    node *adj = v->adj_list;
    while (adj != NULL) {
        int dest = adj->destiny;
        if (!()) {
            dfs(adj->destiny);
        } else {
            // A cycle has been found
            // Add code here to record or print the cycle
        }
        adj = adj->next;
    }
    v->visited = false;
}

int main(){

    graph *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 4 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false, 0);
    insert_edge(&list1, 0, 2, false, 0);
    insert_edge(&list1, 0, 3, false, 0);
    insert_edge(&list1, 1, 3, false, 0);
    insert_edge(&list1, 2, 1, false, 0);
    insert_edge(&list1, 2, 4, false, 0);

    DFS(list1, 1);

    return 0;
}