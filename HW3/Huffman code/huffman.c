#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct node
{
    struct node *left;
    struct node *right;
    char letter;
    int freq;
} Node;

Node *n[MAX], *tree;
int len;

int find(Node *n[], int different)
{
    int small, i;
    i = 0;
    while (n[i]->freq == -1)
        i++;
    small = i;
    if (i == different)
    {
        i++;
        while (n[i]->freq == -1)
            i++;
        small = i;
    }
    for (i = 1; i < len; i++)
    {
        if (n[i]->freq == -1)
            continue;
        if (i == different)
            continue;
        if (n[i]->freq < n[small]->freq)
            small = i;
    }
    return small;
}

void Table(int table[], Node *tree, int Code)
{
    if (tree->letter != 0)
        table[(int)tree->letter - 'A'] = Code;
    else
    {
        Table(table, tree->left, Code * 10 + 1);
        Table(table, tree->right, Code * 10 + 2);
    }
    return;
}

void invert(int table[],int table2[])
{
    int i, n, copy;
    for (i = 0; i < 26; i++)
    {
        n = table[i];
        copy = 0;
        while (n > 0)
        {
            copy = copy * 10 + n %10;
            n /= 10;
        }
        table2[i] = copy;
    }
    return;
}

int findmax(int table[], int table2[])
{
    int max, i, j, n;
    char bit;
    max = 0;
    for (i = 0; i < 26; i++)
        if (max < table[i])
        {
            max = table[i];
            j = i;
        }
    table[j] = 0;
    printf("%c ", j + 'A');
    n = table2[j];
    while(n != 0)
    {
        bit = n % 10 - 1;
        printf("%d", bit);
        n /= 10;
    }
    printf("\n");
}

int main(void)
{
    int N, i, j, s1, s2, table[26], table2[26], max;
    char L[MAX];
    Node *temp;
    scanf("%d", &N);
    while(N--)
    {
        scanf("\n");
        gets(L);
        len = strlen(L) / 2 + 1;
        j = 0;
        for (i = 0; i < len; i++)
        {
            n[i] = (Node *)malloc(sizeof(Node));
            n[i]->letter = L[j];
            scanf("%d", &n[i]->freq);
            j += 2;
        }
        scanf("%d", &i);
        for (i = 0; i < len - 1; i++)
        {
            s1 = find(n, -1);
            s2 = find(n, s1);
            temp = n[s1];
            n[s1] = (Node *)malloc(sizeof(Node));
            n[s1]->freq = temp->freq + n[s2]->freq;
            n[s1]->letter = 0;
            n[s1]->left = n[s2];
            n[s1]->right = temp;
            n[s2]->freq = -1;
        }
        tree = n[s1];
        for (i = 0; i < 26; i++)
        {
            table[i] = 0;
            table2[i] = 0;
        }
        Table(table, tree, 0);
        invert(table, table2);
        for (i = 0; i < len; i++)
            findmax(table, table2);
    }
    return 0;
}
