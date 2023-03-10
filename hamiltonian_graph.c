#include "graph.c"

bool is_adjacency(
    graph *list,
    int vertex_origin_id,
    int vertex_destiny_id)
{
    return is_destiny_on_node_list(
        list->vertex_list[vertex_origin_id]->adj_list,
        vertex_destiny_id);
}

bool is_hamiltonian_by_ore_theorem(graph *list)
{
    // Cria grafo com listas de não-adjacência
    graph *non_adjacency_list_graph = NULL;
    init_graph(&non_adjacency_list_graph);

    // Armazena tamanho da lista
    int list_size = list->vertex_list_size;

    // Copia vértices do grafo original
    for (int i = 0; i < list_size; i++)
    {
        insert_vertex(&non_adjacency_list_graph);
        non_adjacency_list_graph->vertex_list[i]->id = list->vertex_list[i]->id;
    }

    // Cálcula grau de saída de cada vértice
    for (int i = 0; i < list_size; i++)
    {
        list->vertex_list[i]->out_degree = get_out_degree(
            list,
            list->vertex_list[i]->id);
    }

    // Copia número de exclusões do grafo original
    non_adjacency_list_graph->del_count = list->del_count;

    // Popula listas de nâo-adjacência
    for (int i = 0; i < list_size; i++)
    {
        list->vertex_list[i]->visited = true;
        for (int j = 0; j < list_size; j++)
        {
            if (!list->vertex_list[j]->visited)
            {
                if (!is_adjacency(
                        list,
                        list->vertex_list[i]->id,
                        list->vertex_list[j]->id))
                {
                    insert_edge(
                        &non_adjacency_list_graph,
                        non_adjacency_list_graph->vertex_list[i]->id,
                        non_adjacency_list_graph->vertex_list[j]->id,
                        true,
                        0);
                }
            }
        }
    }

    /*
     * Verifica condição de Ore: para que um grafo G seja hamiltoniano a soma
     * dos graus de cada par de vértices não-adjacentes deve ser no mínimo igual
     * ao número de vértices de G
     */

    for (int i = 0; i < list_size; i++)
    {
        // Armazena vértice atual
        vertex *current_vertex = list->vertex_list[i];

        // Armazena a não-adjacência atual
        node *current_edge = non_adjacency_list_graph->vertex_list[i]->adj_list;

        // Percorre as adjacências e verifica condição de Ore
        while (current_edge != NULL)
        {
            int out_degree_current_edge = get_out_degree(
                list,
                current_edge->destiny);
            if (
                current_vertex->out_degree +
                    out_degree_current_edge <
                list_size)
            {
                destroy_graph(&non_adjacency_list_graph);
                return false;
            }
            current_edge = current_edge->next;
        }
    }
    destroy_graph(&non_adjacency_list_graph);
    return true;
}

bool is_hamiltonian_by_dirac_theorem(graph *list)
{
    for (int i = 0; i < list->vertex_list_size; i++)
    {
        int out_degree = get_out_degree(list, list->vertex_list[i]->id);

        if (out_degree < (list->vertex_list_size / 2))
        {
            return false;
            break;
        }
    }
    return true;
}

bool is_hamiltonian(graph *list)
{
    if (
        is_hamiltonian_by_ore_theorem(list) ||
        is_hamiltonian_by_dirac_theorem(list))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    graph *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 4 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    insert_edge(&list1, 0, 1, false, 1);
    insert_edge(&list1, 0, 2, false, 2);
    insert_edge(&list1, 0, 3, false, 3);
    insert_edge(&list1, 1, 3, false, 4);
    insert_edge(&list1, 2, 1, false, 5);
    insert_edge(&list1, 2, 4, false, 6);

    is_hamiltonian(list1);

    return 0;
}