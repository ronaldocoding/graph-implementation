#include <stdio.h>
#include <limits.h>

using namespace std;

int *floyd_warshall(
    int **adj, 
    int cities_qtt, 
    int queries_qtt, 
    int *origin, 
    int *destiny, 
    int *cities, 
    int cities_range_max
)
{

    int dist[cities_qtt][cities_qtt];

    for (int i = 0; i < cities_qtt; i++)
    {

        for (int j = 0; j < cities_qtt; j++)
        {
            dist[i][j] = adj[i][j];
        }
    }

    int *cost = new int[queries_qtt];

    for (int k = 0; k <= cities_range_max; k++)
    {
        for (int i = 0; i < cities_qtt; i++)
        {
            for (int j = 0; j < cities_qtt; j++)
            {
                if (
                    dist[i][j] > (dist[i][k] + dist[k][j]) &&
                    (dist[k][j] != INT_MAX && dist[i][k] != INT_MAX)
                )
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        for (int l = 0; l < queries_qtt; l++)
        {
            if (k < cities[l])
            {
                cost[l] = dist[origin[l]][destiny[l]];
            }
            else if (k == 0)
            {
                cost[l] = adj[origin[l]][destiny[l]];
            }
        }
    }

    return cost;
}

int main()
{

    int cities_qtt;
    int connections_qtt;
    int instances_qtt = 0;

    while (scanf("%d %d", &cities_qtt, &connections_qtt) != EOF)
    {

        int **adj;

        adj = new int *[cities_qtt];

        for (int i = 0; i < cities_qtt; i++)
        {
            adj[i] = new int[cities_qtt];
            for (int j = 0; j < cities_qtt; j++)
            {
                if (i != j)
                {
                    adj[i][j] = INT_MAX;
                }
                else
                {
                    adj[i][j] = 0;
                }
            }
        }

        int origin_vertex, destiny_vertex, cost;

        for (int i = 0; i < connections_qtt; i++)
        {
            scanf("%d %d %d", &origin_vertex, &destiny_vertex, &cost);

            if (adj[origin_vertex - 1][destiny_vertex - 1] > cost)
            {
                adj[origin_vertex - 1][destiny_vertex - 1] = cost;
            }
        }

        int queries_qtt;
        scanf("%d", &queries_qtt);

        int *origin = new int[queries_qtt];
        int *destiny = new int[queries_qtt];
        int *cities = new int[queries_qtt];

        int cities_range_max = 0;

        for (int i = 0; i < queries_qtt; i++)
        {
            int origin_city, destiny_city, cities_range;

            scanf("%d %d %d", &origin_city, &destiny_city, &cities_range);

            origin[i] = origin_city - 1; 
            destiny[i] = destiny_city - 1;
            cities[i] = cities_range;

            if (cities_range > cities_range_max)
                cities_range_max = cities_range;
        }

        int *costs = floyd_warshall(
            adj, 
            cities_qtt, 
            queries_qtt, 
            origin, 
            destiny, 
            cities, 
            cities_range_max
        );


        printf("Instancia %d\n", ++instances_qtt);

        for (int q = 0; q < queries_qtt; q++)
        {

            if (costs[q] < INT_MAX)
            {
                printf("%d\n", costs[q]);
            }
            else
            {
                printf("%d\n", -1);
            }
        }

        printf("\n");
    }

    return 0;
}