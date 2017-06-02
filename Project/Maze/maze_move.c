#include <stdio.h>
#include <conio.h>
#include <windows.h>
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
int st_row, st_col, ex_row, ex_col, money, N;

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

BOOL gotoxy(int x, int y)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // handle of Get stdout
    if (hOutput == INVALID_HANDLE_VALUE) return FALSE; // Can't get
    COORD cc;
    cc.X = (SHORT) x;
    cc.Y = (SHORT) y;
    return SetConsoleCursorPosition(hOutput, cc); // set cursor
}

int Clean()
{
    int i, j;
    char c = ' ';
    getch();
    for (i = 0; i < N * 2 + 1; i++)
    {
        for (j = 0; j < N * 2; j++)
            putchar(c);
        printf("\n");
    }
}

int PRINT(element position)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if (i == position.row && j == position.col)
                printf(" @");
            else
            {
                if (i == st_row && j == st_col)
                    printf(" S");
                else if (i == ex_row && j == ex_col)
                    printf(" E");
                else
                {
                    if (maze[i][j] == 1)
                        printf(" -");
                    if (maze[i][j] == 2)
                        printf(" $");
                    if (maze[i][j] == 0)
                        printf("  ");
                }
            }
        }
        printf("\n");
    }
    printf("money $ :  %d", money);
    gotoxy(0, 0);
    Clean();
    gotoxy(0, 0);
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
        PRINT(position);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 4 && !found)
        {
            if (dir == 3)
            {
                position.row = row;
                position.col = col;
                position.dir = dir;
                PRINT(position);
            }
            next_row = row + MOVE[dir].vert;
            next_col = col + MOVE[dir].horiz;
            if (next_row == ex_row && next_col == ex_col)
            {
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                PRINT(position);
                if (maze[next_row][next_col] == 2)
                {
                    money++;
                    maze[next_row][next_col] = 0;
                }
                position.row = next_row;
                position.col = next_col;
                position.dir = 0;
                found = 1;
                PRINT(position);
            }
            else if (maze[next_row][next_col] != 1 && visit[next_row][next_col] == 0)
            {
                visit[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                PRINT(position);
                top++;
                add(top, position.row, 1);
                add(top, position.col, 2);
                add(top, position.dir, 3);
                row = next_row;
                col = next_col;
                dir = 0;
                if (maze[row][col] == 2)
                {
                    money++;
                    maze[row][col] = 0;
                }
            }
            else ++dir;
        }
    }
}

int main(void)
{
    int i, j, result;
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
        printf("The game is end.\n");
    }
    fclose(fPtr);
    return 0;
}
