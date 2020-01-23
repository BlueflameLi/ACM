#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#define inf 0x3f3f3f3f
using namespace std;

int n, m, t, S, s;
struct edge
{
    int w;
    int v;
    int next;
} e[20010];
int tot;
int head[20010];
int dis[1005];
bool vis[1005];
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
    while (~scanf("%d%d%d",&n,&m,&t))       //cin会TLE
    {
        tot = 0;
        memset(head, 0, sizeof(head));
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            scanf("%d%d%d",&u,&v,&w);
            add(u, v, w);
        }
        scanf("%d",&S);
        for (int i = 0; i < S; i++)         //加一个起点的起点，这样就成单源最短路了
        {
            scanf("%d",&s);
            add(0, s, 0);
        }
        dijkstra();
        if (dis[t] == inf)
             printf("-1\n");
        else
            printf("%d\n",dis[t]);
    }
    return 0;
}