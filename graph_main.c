#include "graph.c"

int main()
{
    graph  *list1 = NULL;

    // Inicializa um grafo vazio
    init_graph(&list1);

    // Adiciona 5 vértices
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);
    insert_vertex(&list1);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 1 
     * de peso 10
    */ 
    insert_edge(&list1, 0, 1, false, 10);

    /*
     * Adiciona uma aresta unidirecional entre os vértices de índices 0 e 2, ou
     * seja, é possível ir do vértice de índice 0 para o de índice 2, mas
     * não o contrário (até o momento). Essa aresta tem peso 0
    */ 
    insert_edge(&list1, 0, 2, false, 1);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 0 e 3 
     * de peso 20
    */ 
    insert_edge(&list1, 0, 3, false, 20);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 3 
     * de peso 5
    */ 
    insert_edge(&list1, 1, 3, false, 5);

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 1 e 4 
     * de peso 12
    */ 
    insert_edge(&list1, 1, 4, false, 12);

    /*
     * Adiciona uma aresta unidirecional entre os vértices de índices 2 e 3 
     * de peso 8
    */ 
    insert_edge(&list1, 2, 3, false, 8);

    /*
     * Adiciona uma aresta unidirecional entre os vértices de índices 3 e 4 
     * de peso 18
    */ 
    insert_edge(&list1, 3, 4, false, 18);

    // Mostra o grafo
    show_graph(list1);
    printf("=================\n");

    // Remove o vértice de índice 3
    //remove_vertex(&list1, 3);

    // Insere mais dois vértices
    insert_vertex(&list1);
    insert_vertex(&list1);

    // Mostra o grafo
    show_graph(list1);
    printf("=================\n");

    remove_vertex(&list1, 4);

    show_graph(list1);
    printf("=================\n");

    // Insere um vértice
    insert_vertex(&list1);

    // Mostra o grafo
    show_graph(list1);
    printf("=================\n");

    /*
     * Adiciona uma aresta bidirecional entre os vértices de índices 2 e 7 
     * de peso 30
    */ 
    insert_edge(&list1, 2, 7, false, 30);

    /*
     * Tenta adicionar uma aresta bidirecional entre os vértices de índices 2 e 4 
     * de peso 16, mas como o vértice de índice 4 não existe, essa aresta não é
     * adicionada
    */
    insert_edge(&list1, 2, 4, true  , 16);

    // Mostra o grafo
    show_graph(list1);
    printf("=================\n");


    // Destrói o grafo (limpa todos as arestas e vértices da memória)
    //destroy_graph(&list1);

    // Mostra o grafo vazio
    show_graph(list1);
    printf("=================\n");
  
    /*
     * Obs: nessa implementação de grafos, quando todas as arestas são
     * inseridas como bidirecionais, temos um grafo não-direcionado, ou seja,
     * não existe um sentido entre as arestas. No entanto, quando inserimos no
     * mínimo uma aresta unidirecional, temos um grafo direcionado, mesmo que
     * todas as outras arestas sejam bidirecionais
    */
}