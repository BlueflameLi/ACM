#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;

int dx[6] = {1, 0, -1, 0, 0, 0};
int dy[6] = {0, 1, 0, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
int map[55][55][55];
int v[55][55][55];
int a, b, c, t, T;
struct node
{
    int x, y, z, step;
} s;
bool check(node p)
{
    if (p.x < 0 || p.y < 0 || p.z < 0)
        return false;
    if (p.x >= a || p.y >= b || p.z >= c)
        return false;
    if (map[p.x][p.y][p.z])
        return false;
    if (v[p.x][p.y][p.z])
        return false;
    return true;
}
void bfs()
{
    memset(v, 0, sizeof(v));
    queue<node> q;
    node p, next;
    s.x = 0;
    s.y = 0;
    s.z = 0;
    s.step = 0;
    v[s.x][s.y][s.z] = 1;
    q.push(s);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        for (int i = 0; i < 6; i++)
        {
            next.x = p.x + dx[i];
            next.y = p.y + dy[i];
            next.z = p.z + dz[i];
            if (check(next))
            {
                next.step = p.step + 1;
                if (next.x == a - 1 && next.y == b - 1 && next.z == c - 1)
                {
                    printf("%d\n", next.step);
                    return;
                }
                if (next.step > t)              //超时了就不用再试下去了
                    break;
                v[next.x][next.y][next.z] = 1;
                q.push(next);
            }
        }
    }
    printf("%d\n", -1);
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &t);
        for (int i = 0; i < a; i++)
            for (int j = 0; j < b; j++)
                for (int k = 0; k < c; k++)
                    scanf("%d", &map[i][j][k]); //这题真的一定要用scanf
        if (map[a - 1][b - 1][c - 1] || a + b + c - 3 > t)
        {                                       //如果门前是墙，或者直接冲过去都来不及
            printf("%d\n", -1);                 //那就不用试了
            continue;
        }
        bfs();
    }

    return 0;
}