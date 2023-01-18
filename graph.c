#include <stdio.h>
#include <stdlib.h>
#include "node.c"

typedef struct vertex
{
    int id;
    node *adj_list;
} vertex;

typedef struct vertex_list
{
    int vertex_list_size;
    vertex **vertex_list;
} vertex_list;

void insert_vertex(vertex_list **list)
{
    int index = (*list)->vertex_list_size;

    (*list)->vertex_list[index] = malloc(sizeof(vertex));
    (*list)->vertex_list[index]->id = index;
    (*list)->vertex_list[index]->adj_list = NULL;

    (*list)->vertex_list_size++;

    (*list)->vertex_list = realloc((*list)->vertex_list, sizeof(vertex *) * (*list)->vertex_list_size);
    (*list)->vertex_list[index + 1] = NULL;
}

void init_graph(vertex_list **list)
{
    (*list) = malloc(sizeof(list));
    (*list)->vertex_list = malloc(sizeof(vertex *) * 1);
    (*list)->vertex_list_size = 0;
    (*list)->vertex_list[0] = NULL;
}

bool insert_edge(vertex_list **list, int vertex_a_id, int vertex_b_id)
{
    vertex *vertex_a = NULL, *vertex_b = NULL;

    for (int i = 0; i < (*list)->vertex_list_size; i++)
    {
        if ((*list)->vertex_list[i]->id == vertex_a_id)
        {
            vertex_a = (*list)->vertex_list[i];
        }

        if ((*list)->vertex_list[i]->id == vertex_b_id)
        {
            vertex_b = (*list)->vertex_list[i];
        }
    }

    if (vertex_a == NULL || vertex_b == NULL)
    {
        return false;
    }

    insert_node(&vertex_a->adj_list, vertex_b->id);
    insert_node(&vertex_b->adj_list, vertex_a->id);

    return true;
}

int main()
{
    vertex_list *list1 = NULL;
    init_graph(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_edge(&list1, 0, 1);
    for (int i = 0; i < list1->vertex_list_size; i++)
    {
        printf("Arestas do vertice %d:\n", list1->vertex_list[i]->id);
        node *atual = list1->vertex_list[i]->adj_list;
        while (atual != NULL)
        {
            printf("%d ", atual->value);
            atual = atual->next;
        }
        printf("\n");
    }
}