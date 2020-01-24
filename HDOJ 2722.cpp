#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#define inf 0x3f3f3f3f
using namespace std;

int n, m, t;
char d;
struct edge
{
    int w;
    int v;
    int next;
} e[20010];
int tot;
int head[20010];
int dis[1050]; //数组要开到21*21以上，我在这卡了两小时。。。
bool vis[1050];
void add(int u, int v, int w)
{
    //cout << u << ' ' << v << ' ' << w << endl;
    e[++tot].v = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}
void dijkstra()
{
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[0] = 0;
    q.push(make_pair(0, 0));
    while (q.size())
    {
        int p = q.top().second;
        q.pop();
        if (vis[p])
            continue;
        vis[p] = 1;
        for (int i = head[p]; i != 0; i = e[i].next)
        {
            if (dis[e[i].v] > dis[p] + e[i].w)
            {
                dis[e[i].v] = dis[p] + e[i].w;
                q.push(make_pair(-dis[e[i].v], e[i].v));
            }
        }
    }
}
int main()
{
    while (cin >> n >> m && n && m)
    {
        tot = 0;
        memset(head, 0, sizeof(head));
        for (int i = 0; i < 2 * n + 1; i++)
            for (int j = 0; j < m + i % 2; j++)
            {
                int k = (i / 2) * (m + 1) + j;  //这个可以自己对着图想象一下
                cin >> t >> d;                  //k是这条路的西或北点
                if (t == 0)         //速度0的直接跳过
                    continue;
                t = 2520 / t;
                if (d == '*')
                {
                    if (i % 2)
                    {
                        add(k, k + m + 1, t);
                        add(k + m + 1, k, t);
                    }
                    else
                    {
                        add(k, k + 1, t);
                        add(k + 1, k, t);
                    }
                }
                else if (d == '<')
                    add(k + 1, k, t);
                else if (d == '>')
                    add(k, k + 1, t);
                else if (d == 'v')
                    add(k, k + m + 1, t);
                else if (d == '^')
                    add(k + m + 1, k, t);
            }
        dijkstra();
        if (dis[(n + 1) * (m + 1) - 1] == inf)
            cout << "Holiday" << endl;
        else
            cout << dis[(n + 1) * (m + 1) - 1] << " blips" << endl;
    }
    return 0;
}
