#include <stdio.h>
#define MAX 110

int matrix[MAX][MAX];

int TopologicalOrdering(int node)
{
    int edge[MAX], i, j, k;
    for (i = 0; i < node; i++)
        edge[i] = 0;
    for (i = 0; i < node; i++)
        for (j = 0; j < node; j++)
            if (matrix[i][j])
                edge[j]++;
    for (i = 0; i < node; i++)
    {
        k = 0;
        while(k < node && edge[k] != 0)
            k++;
        if (k == node) break;
        edge[k] = -1;
        for (j = 0; j < node; j++)
            if (matrix[k][j])
                edge[j]--;
    }
    if (k == node)
        return 1;
    else
        return 0;
}

int main(void)
{
    int N, node, i, j;
    scanf("%d", &N);
    while(N--)
    {
        scanf("%d", &node);
        for (i = 0; i < node; i++)
            for (j = 0; j < node; j++)
                scanf("%d", &matrix[i][j]);
        scanf("%d", &j);
        i = TopologicalOrdering(node);
        if (i == 0)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
