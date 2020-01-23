#include <iostream>
#include <queue>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;

int n, m, s;
struct edge
{
    int w;
    int v;
    int next;
} e[20010];
int tot;
int head[20010];
int dis[105];
bool vis[105];
void add(int u, int v, int w)
{
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
    dis[1] = 0;
    q.push(make_pair(0, 1));
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
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            add(u, v, w);
            add(v, u, w);
        }
        dijkstra();
        cout << dis[n] << endl;
    }
    return 0;
}