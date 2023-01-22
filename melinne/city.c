#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 1000
#define MAX_FLIGHTS 10000

struct City {
    int name;
    struct Flight *firstFlight;
};

struct Flight {
    int destination;
    int cost;
    struct Flight *next;
};

struct City cities[MAX_CITIES];
int n, m, t;
int dist[MAX_CITIES][11];

void addFlight(int source, int destination, int cost) {
    struct Flight *flight = (struct Flight*) malloc(sizeof(struct Flight));
    flight->destination = destination;
    flight->cost = cost;
    flight->next = cities[source].firstFlight;
    cities[source].firstFlight = flight;
}

void dijkstra() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= t; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    dist[0][0] = 0;

    for (int k = 0; k < n; k++) {
        for (int j = 0; j <= t; j++) {
            for (struct Flight *f = cities[k].firstFlight; f; f = f->next) {
                if (j > 0) {
                    if (dist[k][j - 1] + f->cost < dist[f->destination][j]) {
                        dist[f->destination][j] = dist[k][j - 1] + f->cost;
                    }
                } else {
                    if (dist[k][j] + f->cost < dist[f->destination][j]) {
                        dist[f->destination][j] = dist[k][j] + f->cost;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &t);

    for (int i = 0; i < n; i++) {
        cities[i].name = i;
    }

    for (int i = 0; i < m; i++) {
        int source, destination, cost;
        scanf("%d %d %d", &source, &destination, &cost);
        addFlight(source, destination, cost);
    }

    dijkstra();

    int minCost = INT_MAX;
    for (int i = 0; i <= t; i++) {
        if (dist[n - 1][i] < minCost) {
            minCost = dist[n - 1][i];
        }
    }

    printf("Minimum cost: %d\n", minCost);

    return 0;
}
