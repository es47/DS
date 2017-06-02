#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int stackC[6], top;

int push(int data)
{
    stackC[top] = data;
}

int pop(void)
{
    top--;
}

int main(void)
{
    int trainA[110], trainB[110], N, i, NinB;
    char line[10000], sep[] = " ", *token;
    while(gets(line) != NULL)
    {
        N = 0;
        token = strtok(line, sep);
        while (token != NULL)
        {
            trainA[N] = atoi(token);
            token = strtok(NULL, sep);
            N++;
        }
        for (i = 0; i < N; i++)
            scanf("%d", &trainB[i]);
        gets(line);
        top = NinB = 0;
        for (i = 0; i < N; i++)
        {
            if (top < 6)
            {
                top++;
                push(trainA[i]);
            }
            while(top != 0 && trainB[NinB] == stackC[top])
            {
                pop();
                NinB++;
            }
        }
        if (NinB == N)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
