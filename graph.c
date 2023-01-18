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

    (*list)->vertex_list = realloc((*list)->vertex_list, sizeof(vertex) * (index + 1));
    (*list)->vertex_list[index + 1] = NULL;
}

void init_graph(vertex_list **list)
{
    (*list) = malloc(sizeof(vertex_list));
    (*list)->vertex_list = malloc(sizeof(vertex *));
    (*list)->vertex_list_size = 0;
    (*list)->vertex_list[0] = NULL;
}

bool insert_edge(vertex_list **list, int origin_vertex_id, int destiny_vertex_id, bool bidirectional)
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

    insert_node(&vertex_origin->adj_list, vertex_destiny->id);

    if (bidirectional)
    {
        insert_node(&vertex_destiny->adj_list, vertex_origin->id);
    }

    return true;
}

bool remove_edge(vertex_list **list, int vertex_a_id, int vertex_b_id)
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

int get_out_degree(vertex_list *list, int vertex_id)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id == vertex_id)
        {
            return get_node_list_size(list->vertex_list[i]->adj_list);
        }
    }
}

int get_in_degree(vertex_list *list, int vertex_id)
{
    int in_degree = 0;
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->id != vertex_id)
        {
            if (is_value_on_node_list(list->vertex_list[i]->adj_list, vertex_id))
            {
                in_degree++;
            }
        }
    }
    return in_degree;
}

void show_graph(vertex_list *list)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        printf("%d: ", list->vertex_list[i]->id);
        node *current_node = list->vertex_list[i]->adj_list;
        while (current_node != NULL)
        {
            printf("%d -> ", current_node->value);
            current_node = current_node->next;
        }
        printf("\n");
    }
}

int main()
{
    vertex_list *list1 = NULL;
    init_graph(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false);
    insert_edge(&list1, 0, 2, false);
    insert_edge(&list1, 0, 3, false);

    insert_edge(&list1, 1, 3, false);
    insert_edge(&list1, 1, 4, false);

    insert_edge(&list1, 2, 3, false);

    insert_edge(&list1, 3, 4, false);

    show_graph(list1);

    remove_edge(&list1, 0, 3);

    show_graph(list1);
    // printf("out degree: %d\n", get_out_degree(list1, 0));
    // printf("in degree: %d\n", get_in_degree(list1, 2));
}