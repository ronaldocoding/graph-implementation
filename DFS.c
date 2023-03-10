#include "graph.c"

void DFS(graph *graph, int vertex_id)
{
    bool visited[graph->vertex_list_size];

    for (int i = 0; i < graph->vertex_list_size; i++)
    {
        visited[i] = false;
    }

    node *stack = NULL;

    push(&stack, create_node(vertex_id, 0, 0));

    printf("Início -> ");
    while (stack != NULL)
    {
        node *current = pop(&stack);
        int vertex_index = get_vertex_index(graph, current->destiny);

        if (!visited[vertex_index])
        {
            printf("%d -> ", current->destiny);
            visited[vertex_index] = true;
        }

        node *adj = graph->vertex_list[vertex_index]->adj_list;

        while (adj != NULL)
        {
            int index = get_vertex_index(graph, adj->destiny);
            if (!visited[index])
            {
                push(&stack, create_node(adj->destiny, 0, adj->weight));
            }
            adj = adj->next;
        }
    }
    printf("Fim\n\n");
}
