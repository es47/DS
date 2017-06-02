#include <stdio.h>
#include <stdlib.h>
#define MAX 1100

typedef struct listnode{
    int vertex;
    struct listnode *next;
}ListNode;

ListNode *map[MAX];
int visit[MAX], E_power[MAX], enemy, edge, power, goal_power, lose, win;

void Insert(int u, int v)
{
    ListNode *p, *q;
    q = (ListNode *)malloc(sizeof (ListNode));
    q->vertex = v;
    q->next = NULL;
    if (map[u] == NULL)
        map[u] = q;
    else
    {
        p = map[u];
        while(p->next != NULL)
            p = p->next;
        p->next = q;
    }
}

void Read_graph()
{
    int i, u, v;
    for (i = 0; i < enemy; i++)
    {
        map[i] = NULL;
        for (i = 0; i < edge; i++)
        {
            scanf("%d %d", &u, &v);
            Insert(u, v);
        }
    }
}

void DFS(int i)
{
    ListNode *p;
    p = map[i];
    visit[i] = 1;
    while(p != NULL && power < goal_power)
    {
        i = p->vertex;
        if (visit[i] == 0)
        {
            if (E_power[i] < power)
            {
                power += E_power[i];
                win++;
                DFS(i);
            }
            else
            {
                visit[i] = 1;
                lose++;
            }
        }
        p = p->next;
    }
}

int main(void)
{
    int i;
    while((scanf("%d", &enemy)) != EOF)
    {
        scanf("%d %d %d", &edge, &power, &goal_power);
        for (i = 0; i < enemy; i++)
            scanf("%d", &E_power[i]);
        Read_graph();
        for (i = 0; i < enemy; i++)
            visit[i] = 0;
        lose = 0;
        win = 1;
        DFS(0);
        printf("%d %d %d\n", lose, win, power);
    }
    return 0;
}
