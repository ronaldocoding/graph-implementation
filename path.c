#include "graph.c"

typedef struct path
{
    node *vertex_ids_list;
    int cost;
    bool is_circuit;
    struct path *next;
} path;

path *create_path(node *vertex_root_id, int cost, bool is_circuit)
{
    path *new_path = (path *)malloc(sizeof(path));
    new_path->vertex_ids_list = vertex_root_id;
    new_path->cost = cost;
    new_path->is_circuit = is_circuit;
    new_path->next = NULL;
    return new_path;
}

void insert_path(path **first, path *new_path)
{
    if (*first != NULL)
        new_path->next = *first;
    *first = new_path;
}

void remove_all_paths(path **first)
{
    while (*first != NULL)
    {
        path *old_first = *first;
        *first = (*first)->next;
        free(old_first);
    }
}

void show_path(path **first)
{
    path *p = *first;
    printf("Início -> ");
    while (p->vertex_ids_list != NULL)
    {
        printf("%d -> ", p->vertex_ids_list->value);
        p->vertex_ids_list = p->vertex_ids_list->next;
    }
    printf("Fim\n");
    printf("Custo: %d\n\n", p->cost);
}

void show_all_paths(path **first_path)
{
    path *aux = *first_path;
    while (aux != NULL) {
        show_path(&aux);
        aux = aux->next;
    }
}