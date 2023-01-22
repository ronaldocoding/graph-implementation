#include "../graph.c"

// Separa os vertices em conjuntos disjuntos
void make_set(vertex_list *Graph, int *parent_set, int *rank){
  int i;
  
    for (i = 0; i < Graph->vertex_list_size; i++)
    {
        parent_set[i] = i;
        rank[i] = 0;
    }
}


// Encontra a raiz do conjunto ao qual o element_id pertence
int find(int *parent_set, int element_id){
  // se o element_id for 'root'
  if(parent_set[element_id] == element_id) return element_id;

  return find(parent_set, parent_set[element_id]);
}


//Une dois conjuntos disjuntos em um só
void union_set( int * parent_set, int *rank, int element_id_a, int  element_id_b){
  int x, y;
  x = find(parent_set, element_id_a);
  y = find(parent_set,element_id_b);
  if(rank[x] < rank[y]){
    parent_set[x] = y; 
  }
  else if(rank[x] > rank[y]){
    parent_set[y] = x;
  }
  else{
    parent_set[y] = x;
    rank[x]++;
  }
}

void kruskal(vertex_list *Graph)
{
    int e = 0, i = 0;
    node *temp;
    int parent[Graph->vertex_list_size], rank[Graph->vertex_list_size];
    make_set(Graph, parent,rank);

    // Ordena as arestas por peso usando Bubble Sort
    for (i = 0; i < Graph->vertex_list_size; i++)
    {
        for (temp = Graph->vertex_list[i]->adj_list; temp; temp = temp->next)
        {
            for (node *temp2 = temp->next; temp2; temp2 = temp2->next)
            {
                if (temp->weight > temp2->weight)
                {
                    int t = temp->weight;
                    temp->weight = temp2->weight;
                    temp2->weight = t;
                }
            }
        }
    }

    printf("----------- ARVORE GERADORA MINIMA COM KRUSKAL -------------\n");
    // Itera por todos as arestas ordenadas e as adiciona na arvore geradora minima (MST)
    for (i = 0; i < Graph->vertex_list_size; i++)
    {
        for (temp = Graph->vertex_list[i]->adj_list; temp; temp = temp->next)
        {
            int x = find(parent, temp->source);
            int y = find(parent, temp->destiny);

            
            if (x != y)
            {
                printf("(%d)----[%d]----(%d)\n", temp->source, temp->weight, temp->destiny);
                e++;
                union_set(parent, rank, x, y);
                if (e == Graph->vertex_list_size - 1)
                    return;
            }
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

    insert_edge(&list1, 0, 1, false, 10); 
    insert_edge(&list1, 0, 2, false, 1);
    insert_edge(&list1, 0, 3, false, 20);
    insert_edge(&list1, 1, 3, false, 5);
    insert_edge(&list1, 1, 4, false, 12);
    insert_edge(&list1, 2, 3, false, 8);
    insert_edge(&list1, 3, 4, false, 18);
    printf("====================== GRAFO ===================\n");
    // Mostra o grafo
    show_graph(list1);  
    printf("==============================================\n");

    kruskal(list1);

    return 0;
}
