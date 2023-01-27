#include "graph.c"

void DFS(vertex_list *graph, int vertex_id)
{
    bool visited[graph->vertex_list_size];

    for (int i = 0; i < graph->vertex_list_size; i++)
    {
        visited[i] = false;
    }

    node *stack = NULL;

    push(&stack, create_node(vertex_id, 0));

    printf("Início -> ");
    while (stack != NULL)
    {
        node *current = pop(&stack);
        int vertex_index = get_vertex_index(graph, current->value);

        if (!visited[vertex_index])
        {
            printf("%d -> ", current->value);
            visited[vertex_index] = true;
        }

        node *adj = graph->vertex_list[vertex_index]->adj_list;

        while (adj != NULL)
        {
            int index = get_vertex_index(graph, adj->value);
            if (!visited[index])
            {
                push(&stack, create_node(adj->value, adj->weight));
            }
            adj = adj->next;
        }
    }
    printf("Fim\n\n");
}
