#include <iostream>
#include <queue>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;

int T, S, D;
struct edge
{
    int w;
    int v;
    int next;
} e[1000000];                    //不知道有多少边就开的大了点
int tot;
int head[1000000];
int dis[1010];
bool vis[1010];
int s[1010];
int d[1010];
void add(int u, int v, int w)   //今天才知道我这个存图的方法叫链式向前星
{                               //此题有重边，我这种方法可以避免重边
    e[++tot].v = v;             //其他存图方法记得判断重边
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}
void dijkstra()             //堆优化的dijkstra
{
    priority_queue<pair<int, int>> q;//first是到点的距离，second是点
    memset(dis, 0x3f, sizeof(dis));
    memset(vis,false,sizeof(vis));
    dis[0] = 0;
    q.push(make_pair(0, 0));        //将起点0入队，距离自然是0
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
            }                       //优先队列默认大根堆，加个负号就是小根堆了
        }
    }
}
int main()
{
    while (cin >> T >> S >> D)
    {
        tot=0;
        memset(head,0,sizeof(head));
        for (int i = 0; i < T; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            add(u, v, w);            //无向图，都存一遍
            add(v, u, w);
        }
        for (int i = 0; i < S; i++)
        {
            cin >> s[i];            //创造一个起点，使其变成单源最短路
            add(0, s[i], 0);
        }
        for (int i = 0; i < D; i++)
        {
            cin >> d[i];            //创造终点
            add(d[i], 1005, 0);
        }
        dijkstra();
        cout<<dis[1005]<<endl;
    }
    return 0;
}