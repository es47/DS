#include <stdio.h>
#include <string.h>
#define MAX 110

int ptr;
char prefix[MAX], infix[MAX];

int BST(int left, int right)
{
    int i;
    if (left > right) return;
    for (i = 0; i <= right; i++)
        if (prefix[ptr] == infix[i]) break;
    if (i != right + 1)
    {
        ptr++;
        BST(left, i - 1);
        BST(i + 1, right);
        printf("%c", infix[i]);
    }
}

int main(void)
{
    int N, length;
    scanf("%d", &N);
    while(N--)
    {
        scanf("%s %s", prefix, infix);
        length = strlen(prefix);
        ptr = 0;
        BST(0, length - 1);
        printf("\n");
    }
    return 0;
}
