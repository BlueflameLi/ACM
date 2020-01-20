#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int t;
int n, m;
int r = 6;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
char map[25][25];
int v[25][25][1 << 10];     //因为拿到钥匙可能还要往回走，所以钥匙状态也要标记
struct node
{
    int x, y;
    int step;
    int key;        //当前钥匙获得状态
} s;
bool check(node p)
{
    if (p.x < 0 || p.y < 0)
        return false;
    if (p.x >= n || p.y >= m)
        return false;
    if (map[p.x][p.y] == '*')
        return false;
    if (v[p.x][p.y][p.key])
        return false;
    return true;
}
void bfs()
{
    queue<node> q;
    q.push(s);
    node next, p;
    memset(v, 0, sizeof(v));
    v[s.x][s.y][s.key] = 1;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p.step >= t - 1) //如果时间只剩1分钟了还没到终点，那么就挂了
            continue;
        for (int i = 0; i < 4; i++)
        {
            next.x = p.x + dx[i];
            next.y = p.y + dy[i];
            next.key = p.key;       //这个千万不能忘记
            //cout << next.x << ' ' << next.y << ' ' << next.key << endl;
            if (check(next))
            {
                next.step = p.step + 1;
                if (map[next.x][next.y] >= 'A' && map[next.x][next.y] <= 'J')
                {
                    if ((next.key & (1 << (map[next.x][next.y] - 'A'))) == 0)
                        continue;           //通过按位与来判断是否获得了钥匙
                }
                if (map[next.x][next.y] >= 'a' && map[next.x][next.y] <= 'j')
                    next.key |= (1 << (map[next.x][next.y] - 'a')); //按位或更新状态
                if (!v[next.x][next.y][next.key])
                {

                    if (map[next.x][next.y] == '^') //到终点了，输出步数，退出
                    {
                        cout << next.step << endl;
                        return;
                    }
                    //cout<<next.x<<' '<<next.y<<' '<<next.step<<' '<<next.key<<endl;
                    v[next.x][next.y][next.key] = 1;
                    q.push(next);
                }
            }
        }
    }
    cout << -1 << endl; //队列都空了还没找到终点，挂了
}
int main()
{
    while (cin >> n >> m >> t)
    {

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == '@')
                {
                    s.x = i; //起始点初始化
                    s.y = j;
                    s.key = 0;
                    s.step = 0;
                }
            }
        bfs();
    }
    return 0;
}