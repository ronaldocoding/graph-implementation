#include <stdio.h>
#include <stdlib.h>
#include "node.c"

typedef struct vertex
{
    int id;
    bool visited;
    int out_degree;
    node *adj_list;
} vertex;

typedef struct graph
{
    int vertex_list_size;
    int del_count;
    vertex **vertex_list;
} graph;

void insert_vertex(graph **list)
{
    int index = (*list)->vertex_list_size;

    (*list)->vertex_list[index] = malloc(sizeof(vertex));
    (*list)->vertex_list[index]->id = index + (*list)->del_count;
    (*list)->vertex_list[index]->adj_list = NULL;

    (*list)->vertex_list_size++;

    (*list)->vertex_list = realloc(
        (*list)->vertex_list, 
        sizeof(vertex) * ((*list)->vertex_list_size + 1)
    );
    (*list)->vertex_list[index + 1] = NULL;
}

void init_graph(graph **list)
{
    (*list) = malloc(sizeof(graph));
    (*list)->vertex_list = malloc(sizeof(vertex *));
    (*list)->vertex_list_size = 0;
    (*list)->del_count = 0;
    (*list)->vertex_list[0] = NULL;
}

bool insert_edge(
    graph **list,
    int origin_vertex_id,
    int destiny_vertex_id,
    bool bidirectional,
    int weight)
{
    vertex *vertex_origin = NULL, *vertex_destiny = NULL;

    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == origin_vertex_id)
        {
            vertex_origin = (*list)->vertex_list[i];
        }

        if ((*list)->vertex_list[i]->id == destiny_vertex_id)
        {
            vertex_destiny = (*list)->vertex_list[i];
        }
    }

    if (vertex_origin == NULL || vertex_destiny == NULL)
    {
        return false;
    }

    insert_node(&vertex_origin->adj_list, vertex_destiny->id, weight);

    if (bidirectional)
    {
        insert_node(&vertex_destiny->adj_list, vertex_origin->id, weight);
    }

    return true;
}

bool remove_edge(graph **list, int vertex_a_id, int vertex_b_id)
{
    bool deleted_a = false, deleted_b = false;

    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_a_id)
        {
            delete_node(&((*list)->vertex_list[i]->adj_list), vertex_b_id);
            deleted_a = true;
        }

        if ((*list)->vertex_list[i]->id == vertex_b_id)
        {
            delete_node(&((*list)->vertex_list[i]->adj_list), vertex_a_id);
            deleted_b = true;
        }

        if (deleted_a && deleted_b)
        {
            return true;
        }
    }

    return false;
}

bool remove_vertex(graph **list, int vertex_id)
{
    bool vertex_exists = false;
    int vertex_pos;
    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_id)
        {
            vertex_exists = true;
            vertex_pos = i;
        }
        else
        {
            delete_node(&((*list)->vertex_list[i]->adj_list), vertex_id);
        }
    }
    if (!vertex_exists)
    {
        return false;
    }

    free((*list)->vertex_list[vertex_pos]);

    for (int i = vertex_pos; i < (*list)->vertex_list_size - 1; i++)
    {
        (*list)->vertex_list[i] = (*list)->vertex_list[i + 1];
    }
    free((*list)->vertex_list[(*list)->vertex_list_size]);

    (*list)->del_count++;
    (*list)->vertex_list_size--;

    (*list)->vertex_list = realloc(
        (*list)->vertex_list, 
        sizeof(vertex) * ((*list)->vertex_list_size + 1)
    );
    (*list)->vertex_list[(*list)->vertex_list_size] = NULL;

    return true;
}

void destroy_graph(graph **list)
{
    if ((*list)->vertex_list[0] == NULL)
    {
        (*list)->del_count = 0;
        return;
    }
    remove_vertex(list, (*list)->vertex_list[0]->id);
    destroy_graph(list);
}

int get_out_degree(graph *list, int vertex_id)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id == vertex_id)
        {
            return get_node_list_size(list->vertex_list[i]->adj_list);
        }
    }
    return 0;
}

int get_in_degree(graph *list, int vertex_id)
{
    int in_degree = 0;
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id != vertex_id)
        {
            if (is_value_on_node_list(
                list->vertex_list[i]->adj_list, 
                vertex_id))
            {
                in_degree++;
            }
        }
    }
    return in_degree;
}

void show_graph(graph *list)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        printf("%d: ", list->vertex_list[i]->id);
        node *current_node = list->vertex_list[i]->adj_list;
        while (current_node != NULL)
        {
            printf("(%d) %d -> ", current_node->weight, current_node->value);
            current_node = current_node->next;
        }
        printf("\n");
    }
}

// int main()
// {
//     vertex_list *list1 = NULL;

//     // Inicializa um grafo vazio
//     init_graph(&list1);

//     // Adiciona 5 vértices
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);
//     insert_vertex(&list1);

//     /*
//      * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 1
//      * de peso 10
//      */
//     insert_edge(&list1, 0, 1, true, 10);

//     /*
//      * Adiciona uma aresta unidirecional entre os vértices de índices 0 e 2, ou
//      * seja, é possível ir do vértice de índice 0 para o de índice 2, mas
//      * não o contrário (até o momento). Essa aresta tem peso 0
//      */
//     insert_edge(&list1, 0, 2, false, 0);

//     /*
//      * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 3
//      * de peso 20
//      */
//     insert_edge(&list1, 0, 3, true, 20);

//     /*
//      * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 3
//      * de peso 5
//      */
//     insert_edge(&list1, 1, 3, true, 5);

//     /*
//      * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 4
//      * de peso 12
//      */
//     insert_edge(&list1, 1, 4, true, 12);

//     /*
//      * Adiciona uma aresta unidirecional entre os vértices de índices 2 e 3
//      * de peso 8
//      */
//     insert_edge(&list1, 2, 3, false, 8);

//     /*
//      * Adiciona uma aresta unidirecional entre os vértices de índices 3 e 4
//      * de peso 18
//      */
//     insert_edge(&list1, 3, 4, false, 18);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     // Remove o vértice de índice 3
//     remove_vertex(&list1, 3);

//     // Insere mais dois vértices
//     insert_vertex(&list1);
//     insert_vertex(&list1);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     remove_vertex(&list1, 4);

//     show_graph(list1);
//     printf("=================\n");

//     // Insere um vértice
//     insert_vertex(&list1);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     /*
//      * Adiciona uma aresta bidirecional entre os vértices de índices 2 e 7
//      * de peso 30
//      */
//     insert_edge(&list1, 2, 7, true, 30);

//     /*
//      * Tenta adicionar uma aresta bidirecional entre os vértices de índices 2 e 
//      * 4 de peso 16, mas como o vértice de índice 4 não existe, essa aresta não 
//      * é adicionada
//      */
//     insert_edge(&list1, 2, 4, true, 16);

//     // Mostra o grafo
//     show_graph(list1);
//     printf("=================\n");

//     // Destrói o grafo (limpa todos as arestas e vértices da memória)
//     destroy_graph(&list1);

//     // Mostra o grafo vazio
//     show_graph(list1);
//     printf("=================\n");

//     /*
//      * Obs: nessa implementação de grafos, quando todas as arestas são
//      * inseridas como bidirecionais, temos um grafo não-direcionado, ou seja,
//      * não existe um sentido entre as arestas. No entanto, quando inserimos no
//      * mínimo uma aresta unidirecional, temos um grafo direcionado, mesmo que
//      * todas as outras arestas sejam bidirecionais
//      */
// }