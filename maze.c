#include <stdio.h>
#include <stdlib.h>

char maze[100][100];
int startX, startY, endX, endY, n, m;
int flag[100][100];
int jump[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int step;
int ans = 100000;

void dfs(int x, int y, int step);
/**
 * @brief  走迷宫
 * @note   我偷懒了，直接DFS，
 *          1.输入的迷宫用 * 表示障碍，用 . 表示通路，
 *          2.终点位置需要输入T
 *          3.最开始需要输入迷宫大小
 *          4.最后要输入开始和起始坐标
 *          5.程序会生成一个较为正常的迷宫，提供输入者修改
 *          6.最重要的一点！！！这个程序是直接改的我自己之前写的迷宫问题的代码，所以有些古怪（懒得自己再写一个回溯了）
 * 输入模板：
 *          5 5
 *          .....
 *          .*.*.
 *          .*S*.
 *          .***.
 *          ...T*
 *          2 2 4 3
 * 
 * 输出结果：
 *          (2,2)->(1,2)->(0,2)->(0,1)->(0,0)->(1,0)->(2,0)->(3,0)->(4,0)->(4,1)->(4,2)->(0,2)->(0,3)->(0,4)->(1,4)->(2,4)->(1,2)
 * @retval 
 */
int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", &maze[i]);
    }
    scanf("%d%d%d%d", &startX, &startY, &endX, &endY);
    for (int i = -1; i <= n; i++)
    {
        for (int j = -1; j <= m; j++)
        {
            if (-1 == j || -1 == i || n == i || m == j)
            {
                printf("#");
                continue;
            }
            if ((i == startX && j == startY))
            {
                printf("S");
                continue;
            }
            if ('.' == maze[i][j])
            {
                printf(" ");
            }
            else if ('*' == maze[i][j])
            {
                printf("#");
            }
            else
            {
                printf("T");
            }
        }
        printf("\n");
    }
    dfs(startX, startY, 0);
    //printf("%d", ans);

    return 0;
}

void dfs(int x, int y, int step)
{
    if (maze[x][y] == 'T')
    {
        if (step < ans)
        {
            ans = step;
        }
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int curx = x + jump[i][0];
        int cury = y + jump[i][1];
        if (curx >= 0 && curx < n && cury >= 0 && cury < m && flag[curx][cury] == 0 && maze[curx][cury] != '*')
        {
            printf("%s(%d,%d)",(startX == x && startY == y) ? "": "->", x, y);
            flag[curx][cury] = 1;
            dfs(curx, cury, step + 1);
            flag[curx][cury] = 0;
        }
    }
}
