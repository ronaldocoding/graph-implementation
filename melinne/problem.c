#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define MAXN 110
#define INF INT_MAX
int n, m, c, t;
int dist[MAXN][11];
int order[MAXN];

struct Flight {
    int destination;
    int cost;
    struct Flight *next;
};

struct City {
    int name;
    struct Flight *firstFlight;
};

struct City cities[MAXN];

void dijkstra() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= t; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = 0;
    printf("djkstra");
    for (int k = 0; k < n; k++) {
        for (int j = 0; j <= t; j++) {
            for (struct Flight *f = cities[order[k]].firstFlight; f; f = f->next) {
                if (j > 0) {
                    if (dist[order[k]][j - 1] + f->cost < dist[f->destination][j]) {
                        printf(" dj: %d | %d",  dist[f->destination][j], dist[order[k]][j - 1] + f->cost);
                        dist[f->destination][j] = dist[order[k]][j - 1] + f->cost;
                    }
                } else {
                    if (dist[order[k]][j] + f->cost < dist[f->destination][j]) {
                        printf(" dj: %d | %d",  dist[f->destination][j],  dist[order[k]][j] + f->cost);
                        dist[f->destination][j] = dist[order[k]][j] + f->cost;
                    }
                }
            }
        }
    }
}

int main() {
    int dist[MAXN][1000];
    int order[MAXN];
    while(scanf("%d %d", &n, &m)!=EOF){
        for (int i = 0; i < n; i++) {
            cities[i].name = i;
    cities[i].firstFlight = NULL;
    }
    printf("\nm: %d n: %d \n", n, m);

        printf("x x x:\n");
        for (int i = 0; i < m; i++) {
        int source, destination, cost;
        printf("[%d] \n", i);
        scanf("%d %d %d",&source, &destination, &cost);
        printf("s: %d | d: %d | c: %d", source, destination, cost);
        struct Flight *flight = (struct Flight*) malloc(sizeof(struct Flight));
        flight->destination = destination;
        flight->cost = cost;
        flight->next = cities[source].firstFlight;
        cities[source].firstFlight = flight;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &order[i]);
        order[i]--; // adjust for 0-indexing
    }
    
    printf("\n c:\n");
    scanf("%d", &c);
    dijkstra();

    printf("MATRIZ\n");
    for(int i = 0; i < MAXN; i++){
        for(int j = 0; j < MAXN; j++){
            printf("[%d][%d]=%d", i, j, dist[i][j]);
        }
    }

    int l=0;
    printf("Instancia %d\n", ++l);
    for(int i=1;i<=c;++i){
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        printf("\n %d %d %d", u, v, t);
        if(dist[u-1][t]==INF) printf("-1\n");
        else printf(" distancia: %d \n", dist[u-1][t]);
    }
    printf("\n");
}
return 0;
}