#include "../graph.c"


void dfs(vertex_list *graph, int pos){
    pos++;
    graph->vertex_list[pos]->visited = true;
    printf("%d ", graph->vertex_list[pos]->id);
    for(int i = 0; i < graph->vertex_list_size; i++){
        if(!(graph->vertex_list[pos]->visited)){
            dfs(graph, graph->vertex_list[pos]->id);
        }
    }
}



int main(){

    vertex_list *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 4 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false, 1);
    insert_edge(&list1, 0, 2, false, 2);
    insert_edge(&list1, 0, 3, false, 3);
    insert_edge(&list1, 1, 3, false, 4);
    insert_edge(&list1, 2, 1, false, 5);
    insert_edge(&list1, 2, 4, false, 6);

    dfs(list1, 0);

    return 0;
}