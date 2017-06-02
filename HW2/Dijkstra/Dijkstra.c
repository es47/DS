#include <stdio.h>
#define MAX 1000

int W[MAX][MAX], D[MAX];

int Dijkstra(int source, int target)
{
    int visit[MAX], min, i, m, d;
    for (i = 0; i < MAX; i++)
    {
        D[i] = MAX;
        visit[i] = 0;
    }
    visit[source] = 1;
    D[source] = 0;
    while(visit[target] == 0)
    {
        min = MAX;
        for(i = 1; i < MAX; i++)
        {
            d = D[source] + W[source][i];
            if(d < D[i] && visit[i] == 0)
                D[i] = d;
            if(min > D[i] && visit[i] == 0)
            {
                min = D[i];
                m = i;
            }
        }
        source = m;
        visit[source] = 1;
    }
}

int main(void)
{
    int N, line, source, target, i, j, u, v, edge;
    scanf("%d", &N);
    while(N--)
    {
        for (i = 0; i < MAX; i++)
            for (j = 0; j < MAX; j++)
            W[i][j] = MAX;
        scanf("%d", &line);
        scanf("%d %d", &source, &target);
        for (i = 0; i < line; i++)
        {
            scanf("%d %d %d", &u, &v, &edge);
            W[u][v] = edge;
        }
        scanf("%d", &i);
        Dijkstra(source, target);
        printf("%d\n", D[target]);
    }
    return 0;
}
