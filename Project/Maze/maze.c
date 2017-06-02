#include <stdio.h>
#define MAX 100

typedef struct
{
    short int vert;
    short int horiz;
} move;
move MOVE[4];

typedef struct
{
    int row;
    int col;
    int dir;
} element;

element stack[MAX];
int maze[MAX][MAX], visit[MAX][MAX];
int st_row, st_col, ex_row, ex_col, money;

int delete(int i,int top)                  /* output number from stack */
{
    if (i == 1)
        return stack[top].row;
    if (i == 2)
        return stack[top].col;
    if (i == 3)
        return stack[top].dir;
}

int add(int top, int position, int i)       /*input number to stack */
{
    if (i == 1)
        stack[top].row = position;
    if (i == 2)
        stack[top].col = position;
    if (i == 3)
        stack[top].dir = position;
}

int path()                                  /* find path */
{
    int top, row, col, dir, next_row, next_col, found = 0;
    element position;
    visit[1][1] = 1;
    top = 0;
    stack[0].row = st_row;
    stack[0].col = st_col;
    stack[0].dir = 1;
    if (maze[st_row][st_col] == 2)
        money++;
    while (top > -1 && !found)
    {
        position.row = delete(1, top);
        position.col = delete(2, top);
        position.dir = delete(3, top);
        top--;
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 4 && !found)
        {
            next_row = row + MOVE[dir].vert;
            next_col = col + MOVE[dir].horiz;
            if (next_row == ex_row && next_col == ex_col)
            {
                if (maze[next_row][next_col] == 2)
                {
                    money++;
                    maze[next_row][next_col] = 0;
                }
                found = 1;
            }
            else if (maze[next_row][next_col] != 1 && visit[next_row][next_col] == 0)
            {
                if (maze[next_row][next_col] == 2)
                {
                    money++;
                    maze[next_row][next_col] = 0;
                }
                visit[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                top++;
                add(top, position.row, 1);
                add(top, position.col, 2);
                add(top, position.dir, 3);
                row = next_row;
                col = next_col;
                dir = 0;
            }
            else ++dir;
        }
    }
}

int main(void)
{
    int N, i, j, result;
    FILE *fPtr;
    MOVE[0].vert = -1, MOVE[0].horiz = 0, MOVE[1].vert = 0, MOVE[1].horiz = 1;
    MOVE[2].vert = 1, MOVE[2].horiz = 0, MOVE[3].vert = 0, MOVE[3].horiz = -1;
    fPtr = freopen("maze.txt", "r", stdin);
    while((scanf("%d", &N)) != EOF)
    {
        scanf("%d %d %d %d", &st_col, &st_row, &ex_col, &ex_row);
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
            {
                scanf("%d", &maze[i][j]);
                visit[i][j] = 0;
            }
        money = 0;
        path();
        printf("%d\n", money);
    }
    fclose(fPtr);
    return 0;
}
