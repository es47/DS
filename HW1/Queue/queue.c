#include <stdio.h>
#define QSIZE 10

int main(void)
{
    int choice, amount, number, head, tail, queue[QSIZE], i;
    scanf("%d", &amount);
    head = 0;
    for (tail = 0; tail < amount; tail++)
        scanf("%d", &queue[tail]);
    tail--;
    while((scanf("%d", &choice)) != EOF)
    {
        if (choice == 1)
        {
            if ((tail + 1) % QSIZE != head)
            {
                scanf("%d", &number);
                tail++;
                tail %= QSIZE;
                queue[tail] = number;
            }
        }
        if (choice == 2)
        {
            if (head % QSIZE != tail % QSIZE)
            {
                head++;
                head %= QSIZE;
            }
        }
    }
    for (i = head % QSIZE; i != (tail + 1) % QSIZE; )
    {
        printf("%d", queue[i]);
        if (i != tail % QSIZE)
            printf(" ");
        i++;
        i %= QSIZE;
    }
    printf("\n");
    return 0;
}
