#include "../graph.c"

/*int * edge_list(vertex_list **Graph){
  vertex_list *copy_graph = *Graph;
  int n_vertex = copy_graph->vertex_list_size;
  Edge_List list;
  for(int i = 0; i < n_vertex; i++){
    int size = get_in_degree(copy_graph, i);
    printf("[%d]---- \n", copy_graph->vertex_list[i]->id); 
    while(copy_graph->vertex_list[i]->adj_list != NULL){
      printf("foi\n");
      if(list.edges[i].source == i && list.edges[i].destiny != 
         copy_graph->vertex_list[i]->adj_list->destiny){
            printf("u: %d \t w: %d\t v: %d \n", copy_graph->vertex_list[i]->adj_list->source, copy_graph->vertex_list[i]->adj_list->weight, copy_graph->vertex_list[i]->adj_list->destiny);
            
      }
       copy_graph->vertex_list[i]->adj_list = copy_graph->vertex_list[i]->adj_list->next;
    }
  }
}*/

void make_set(int number_of_vertices, int *parent_set){
  int i;
  // cria um conjunto disjunto para cada vértice
  for(i = 0; i < number_of_vertices; i++){
    parent_set[i] = i;
  }
}

// Encontra a raiz do conjunto ao qual o element_id pertence
int find(int element_id, int *parent_set){
  // se o element_id for 'root'
  if(parent_set[element_id] == element_id) return element_id;

  return find(parent_set[element_id], parent_set);
}

void union_set(int element_id_a, int  element_id_b, int * parent_set){
  // encontra a raiz dos conjuntos os quais os elementos x e y pertencem
  int x, y;
  x = find(element_id_a, parent_set);
  y = find(element_id_b, parent_set);

  parent_set[x] = y;
}

void kruskal(vertex_list **Graph, int n_vertex, int *parent_set, node *edges){
  node *MST[n_vertex -1];
  int src, dest, weight;
  vertex_list *copy_graph = *Graph;
  make_set(n_vertex, parent_set);
  
  int n;
  for(int i = 0; i < n_vertex -1; i++){
    src = edges[i].source;
    dest = edges[i].destiny;
    weight = edges[i].weight;
   

    int x = find(src, parent_set);
    int y = find(dest, parent_set);

    if(x != y){
      MST[i]->source = src;
      MST[i]->weight = weight;
      MST[i]->destiny = dest;
      union_set(x, y, parent_set);
    }
  }
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
    insert_edge(&list1, 0, 1, true, 10);

    /*
     * Adiciona uma aresta unidirecional entre os vértices de índices 0 e 2, ou
     * seja, é possível ir do vértice de índice 0 para o de índice 2, mas
     * não o contrário (até o momento). Essa aresta tem peso 0
    */ 
    insert_edge(&list1, 0, 2, true, 1);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 3 
     * de peso 20
    */ 
    insert_edge(&list1, 0, 3, true, 20);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 3 
     * de peso 5
    */ 
    insert_edge(&list1, 1, 3, true, 5);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 4 
     * de peso 12
    */ 
    insert_edge(&list1, 1, 4, true, 12);

    /*
     * Adiciona uma aresta unidirecional entre os vértices de índices 2 e 3 
     * de peso 8
    */ 
    insert_edge(&list1, 2, 3, true, 8);

    show_graph(list1);
    vertex_list *graph = list1->vertex_list;

    int n_vertices = list1->vertex_list_size;
    int parent_set[n_vertices];
    for(int i = 0; i < n_vertices; i++){
      printf("[%d]: %d \n", i, parent_set[i]);
    }
    kruskal(&list1, n_vertices, parent_set, NULL);
    printf("----------------------------------\n");
    for(int i = 0; i < n_vertices; i++){
      printf("[%d]: %d \n", i, parent_set[i]);
    }

    int f = find(0, parent_set);
    printf("\n FIND: %d \n", f);
    
}