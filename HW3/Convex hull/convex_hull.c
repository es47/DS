#include <stdio.h>
#define MAX 1000

typedef struct point
{
    int x, y;
}P;
P v[MAX], e[MAX];

int cross(int o1, int o2, int a1, int a2, int b1, int b2)
{
    return (a1 - o1) * (b2 - o2) - (a2 - o2) * (b1 - o1);
}

int cmp(const void *a , const void *b)
{
    P *c = (P *)a;
    P *d = (P *)b;
    if(c->x != d->x)
        return c->x - d->x;
    else
        return c->y - d->y;
}

int main(void)
{
    int i, j, n, m, t;
    i = 0;
    while(scanf("%d", &n) != EOF)
    {
        v[i].x = n;
        scanf("%d", &v[i].y);
        i++;
    }
    qsort(v, i,sizeof(v[0]),cmp);
    m = 0;
    for (j = 0; j < i; j++)
    {
        while (m >= 2 && cross(e[m - 2].x, e[m - 2].y, e[m - 1].x, e[m - 1].y, v[j].x, v[j].y) <= 0)
            m--;
        e[m++] = v[j];
    }
    for (j = i - 2, t = m + 1; j >= 0; j--)
    {
        while (m >= t && cross(e[m - 2].x, e[m - 2].y, e[m - 1].x, e[m - 1].y, v[j].x, v[j].y) <= 0)
            m--;
        e[m++] = v[j];
    }
    m--;
    for (j = 0; j < m; j++)
        printf("%d %d\n", e[j].x, e[j].y);
    return 0;
}
