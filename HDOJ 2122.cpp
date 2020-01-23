#include <iostream>
#include <queue>
#include <cstring>
#include <map>
#define inf 0x3f3f3f3f
using namespace std;

int n;
string S, E;
struct edge
{
    int w;
    int v;
    int next;
} e[20005];
int tot;
int cnt;
int head[20005];
int dis[200];
bool vis[200];
map<string, int> StoI;          //通过map将地名编号，转化成int
void add(int u, int v, int w)
{
    e[++tot].v = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}
void dijkstra()     //dijkstra堆优化
{
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[StoI[S]] = 0;
    q.push(make_pair(0, StoI[S]));
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
    while (cin >> n && n != -1)
    {
        tot = 0;
        cnt = 0;
        memset(head, 0, sizeof(head));
        StoI.clear();           //记得清空
        cin >> S >> E;
        StoI[S] = ++cnt;
        if (!StoI.count(E))     //起点终点可能相等
            StoI[E] = ++cnt;
        for (int i = 0; i < n; i++)
        {
            string u, v;
            int w;
            cin >> u >> v >> w;
            if (!StoI.count(u))
                StoI[u] = ++cnt;
            if (!StoI.count(v))
                StoI[v] = ++cnt;
            add(StoI[u], StoI[v], w);
            add(StoI[v], StoI[u], w);
        }
        dijkstra();
        if (dis[StoI[E]] == inf)        //最后有可能到不了，输出-1
            cout << -1 << endl;
        else
            cout << dis[StoI[E]] << endl;
    }
    return 0;
}