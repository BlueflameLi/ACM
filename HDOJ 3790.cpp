#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#define inf 0x3f3f3f3f
using namespace std;

int n, m, s, t;
struct edge
{
    int w;
    int v;
    int p;
    int next;
} e[100010];
struct node
{
    int x, dist, pay;
    friend bool operator<(node a, node b)
    {                           //重载运算符，使距离最短的，花费小的排在队列前面
        if (a.dist == b.dist)
            return b.pay < a.pay;
        else
            return b.dist < a.dist;
    }
};
int tot;
int head[100010];
int dis[1005];
int cost[1005];
bool vis[1005];
void add(int u, int v, int w, int p)
{
    e[++tot].v = v;
    e[tot].w = w;
    e[tot].p = p;
    e[tot].next = head[u];
    head[u] = tot;
}
void dijkstra()
{
    priority_queue<node> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(cost, 0x3f, sizeof(cost));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    cost[s] = 0;
    node tmp;
    tmp.pay = 0;
    tmp.x = s;
    tmp.dist = 0;
    q.push(tmp);
    while (q.size())
    {
        node tmp = q.top();
        q.pop();
        if (vis[tmp.x])
            continue;
        vis[tmp.x] = 1;
        for (int i = head[tmp.x]; i != 0; i = e[i].next)
        {
            if (dis[e[i].v] > dis[tmp.x] + e[i].w || dis[e[i].v] == dis[tmp.x] + e[i].w && cost[e[i].v] > cost[tmp.x] + e[i].p)
            {
                node next;
                next.x = e[i].v;
                next.dist = dis[e[i].v] = dis[tmp.x] + e[i].w;
                next.pay = cost[e[i].v] = cost[tmp.x] + e[i].p;
                q.push(next);
            }
        }
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m) && n && m)
    {
        tot = 0;
        memset(head, 0, sizeof(head));
        for (int i = 0; i < m; i++)
        {
            int u, v, w, p;                     //cin会tle
            scanf("%d%d%d%d", &u, &v, &w, &p);
            add(u, v, w, p);
            add(v, u, w, p);
        }
        scanf("%d%d", &s, &t);
        dijkstra();
        printf("%d %d\n", dis[t], cost[t]);
    }
    return 0;
}