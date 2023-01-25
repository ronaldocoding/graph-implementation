#include "graph.c"

typedef struct priority_queue
{
    node edge;
    struct priority_queue *next;
} priority_queue;

priority_queue *new_item(node edge)
{
    priority_queue *new_item = malloc(sizeof(priority_queue));
    new_item->edge = edge;
    new_item->next = NULL;
    return new_item;
}

void enqueue(priority_queue **queue, node edge)
{
    if ((*queue) == NULL)
    {
        (*queue) = new_item(edge);
        return;
    }

    priority_queue *current = (*queue);
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_item(edge);
}

node dequeue(priority_queue **queue)
{
    node item = (*queue)->edge;

    priority_queue *new_next = (*queue)->next;
    free((*queue));
    (*queue) = new_next;

    return item;
}

priority_queue *get_priority_queue(graph *list)
{
    priority_queue *queue = NULL;

    for (int i = 0; i < list->vertex_list_size; i++)
    {
        int minimum_weight_value = list->vertex_list[i]->adj_list->weight;
        node *current = list->vertex_list[i]->adj_list, *edge_to_save;
        edge_to_save = current;

        while (current != NULL)
        {
            if (current->weight < minimum_weight_value)
            {
                minimum_weight_value = current->weight;
                edge_to_save = current;
            }
            current = current->next;
        }

        enqueue(&queue, (*edge_to_save));
    }

    return queue;
}

void print_queue(priority_queue *queue)
{
    priority_queue *current = queue;
    int index = 0;
    while (current != NULL)
    {
        printf("%d - Value:%d|Weight:%d\n", index, current->edge.value, current->edge.weight);

        current = current->next;
        index++;
    }
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

    priority_queue *queue = get_priority_queue(list1);
    print_queue(queue);
    printf("=================\n");
}