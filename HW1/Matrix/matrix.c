#include <stdio.h>
#define SIZE 5
int main(void)
{
    int matrix[SIZE][SIZE], i, j, rotate[SIZE][SIZE];
    char turn;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            scanf("%d", &matrix[i][j]);
    while((scanf("\n%c", &turn)) != EOF)
    {
        if (turn == 'L')
        {
            for(i = 0; i < 5; i++)
                for (j = 0; j < 5; j++)
                    rotate[4 - j][i] = matrix[i][j];
        }
        for (i = 0; i < 5; i++)
            for (j = 0; j < 5; j++)
                matrix[i][j] = rotate[i][j];
    }
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%d", rotate[i][j]);
            if (j != 4)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
