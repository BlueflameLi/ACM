#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int map[10][10];
int v[10][10][10][10];
int n, m, t;
struct node
{
    int x, y, bx, by;     //x和y是人的位置，bx和by是箱子的位置
    int step;             //step是箱子移动的步数
    friend bool operator<(node a, node b)
    {
        return a.step > b.step;
    }
} s;
bool check(node p)
{
    if (p.x < 0 || p.y < 0)
        return false;
    if (p.x >= n || p.y >= m)
        return false;
    if (map[p.x][p.y] == 1)
        return false;
    return true;
}
void bfs()
{
    memset(v, 0, sizeof(v));
    priority_queue<node> q;
    node p, next;
    v[s.x][s.y][s.bx][s.by] = 1;
    s.step = 0;
    q.push(s);
    while (!q.empty())
    {
        p = q.top();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            next.x = p.x + dx[i];
            next.y = p.y + dy[i];
            if (check(next))
            {
                next.bx = p.bx;
                next.by = p.by;
                next.step = p.step;
                if (next.x == next.bx && next.y == next.by) //如果人下一步走在了箱子的位置上
                {                                           //那就是在推箱子
                    int tbx = next.bx + dx[i];              //箱子向人走的方向移动一格
                    int tby = next.by + dy[i];
                    if (tbx >= 0 && tbx < n && tby >= 0 && tby < m && map[tbx][tby] != 1)
                    {                                       //判断箱子能否移动
                        next.bx = tbx;
                        next.by = tby;
                        next.step++;
                    }
                }
                if (map[next.bx][next.by] == 3)
                {
                    cout << next.step << endl;
                    return;
                }
                if (!v[next.x][next.y][next.bx][next.by])   //标记重复状态
                {
                    v[next.x][next.y][next.bx][next.by] = 1;
                    q.push(next);
                }
            }
        }
    }
    cout << -1 << endl;
}
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == 4)
                {
                    s.x = i;
                    s.y = j;
                }
                else if (map[i][j] == 2)
                {
                    s.bx = i;
                    s.by = j;
                }
            }
        bfs();
    }

    return 0;
}