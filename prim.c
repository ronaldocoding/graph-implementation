#include <math.h>
#include "graph.c"

typedef struct priority_queue
{
    vertex *current_vertex;
    int key;
    vertex *parent;
    struct priority_queue *next;
} priority_queue;

priority_queue *new_item(vertex *vertex)
{
    priority_queue *new_item = malloc(sizeof(priority_queue));
    new_item->current_vertex = vertex;
    new_item->key = (int)INFINITY;
    new_item->parent = NULL;
    new_item->next = NULL;
    return new_item;
}

void enqueue(priority_queue **queue, vertex *vertex)
{
    if ((*queue) == NULL)
    {
        (*queue) = new_item(vertex);
        return;
    }

    priority_queue *current = (*queue);
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_item(vertex);
}

void enqueue_2(priority_queue **queue, priority_queue *item)
{
    if ((*queue) == NULL)
    {
        (*queue) = item;
        return;
    }

    priority_queue *current = (*queue);
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = item;
}

priority_queue *extract_minimum(priority_queue **queue)
{
    int minimum_weight = (*queue)->key;
    priority_queue *minimum_item = (*queue), *current = (*queue), *before = NULL;

    while (current != NULL)
    {
        if (current->key < minimum_weight)
        {
            minimum_weight = current->key;
            minimum_item = current;
        }
        current = current->next;
    }
    current = (*queue);

    while (current != NULL)
    {
        if (minimum_item == current)
        {
            if (before == NULL)
            {
                (*queue) = minimum_item->next;
            }
            else
            {
                before->next = minimum_item->next;
            }
            minimum_item->next = NULL;
            break;
        }
        before = current;
        current = current->next;
    }

    return minimum_item;
}

priority_queue *get_priority_queue(graph *list)
{
    priority_queue *queue = NULL;

    for (int i = 0; i < list->vertex_list_size; i++)
    {
        if (list->vertex_list[i]->adj_list == NULL)
        {
            continue;
        }

        int minimum_weight_value = list->vertex_list[i]->adj_list->weight;
        node *current = list->vertex_list[i]->adj_list;

        while (current != NULL)
        {
            if (current->weight < minimum_weight_value)
            {
                minimum_weight_value = current->weight;
            }
            current = current->next;
        }

        enqueue(&queue, ((*list).vertex_list[i]));
    }

    return queue;
}

priority_queue *get_vertex_by_edge(priority_queue *queue, node *edge)
{
    priority_queue *current = queue;

    while (current != NULL)
    {
        if (current->current_vertex->id == edge->destiny)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

graph *convert_queue_to_graph(priority_queue *queue)
{
    graph *mst_graph = NULL;
    init_graph(&mst_graph);
    priority_queue *current = queue;
    while (current != NULL)
    {
        insert_vertex(&mst_graph);
        current = current->next;
    }
    current = queue;

    while (current != NULL)
    {
        if (current->parent == NULL)
        {
            current = current->next;
            continue;
        }
        insert_edge(&mst_graph, current->parent->id, current->current_vertex->id, true, current->key);
        current = current->next;
    }

    return mst_graph;
}

graph *prim(graph **list)
{
    priority_queue *queue = get_priority_queue((*list)), *used_queue = NULL;

    (*queue).key = 0;

    while (queue != NULL)
    {
        priority_queue *item = extract_minimum(&queue);
        enqueue_2(&used_queue, item);
        vertex *current_vertex = item->current_vertex;
        node *current_edge = current_vertex->adj_list;

        while (current_edge != NULL)
        {
            priority_queue *adj_vertex = get_vertex_by_edge(queue, current_edge);

            if (adj_vertex == NULL)
            {
                current_edge = current_edge->next;
                continue;
            }

            if (current_edge->weight < adj_vertex->key)
            {
                adj_vertex->key = current_edge->weight;
                adj_vertex->parent = current_vertex;
            }
            current_edge = current_edge->next;
        }
    }

    return convert_queue_to_graph(used_queue);
}

int main()
{
    graph *list1 = NULL;

    init_graph(&list1);

    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, true, 3);
    insert_edge(&list1, 0, 2, true, 5);
    insert_edge(&list1, 0, 3, true, 8);
    insert_edge(&list1, 0, 4, true, 9);

    insert_edge(&list1, 1, 3, true, 2);

    insert_edge(&list1, 3, 2, true, 8);
    insert_edge(&list1, 3, 4, true, 1);

    insert_edge(&list1, 4, 2, true, 2);

    show_graph(list1);
    printf("=================\n");

    show_graph(prim(&list1));
    printf("=================\n");
}