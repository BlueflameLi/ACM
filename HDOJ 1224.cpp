#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int cnt = 1;
int n, m, t, tot;
int point[105];     //存每个点的interesting point
bool map[105][105]; //是否可以straight flight
int dis[105];
bool vis[105];
int pre[105];

void init()
{
    tot = 0;
    memset(dis, 0, sizeof(dis));
    memset(pre, 0, sizeof(pre));
    memset(point, 0, sizeof(point)); //point可以不清空但point[n+1]必须是0
    memset(map, false, sizeof(map));
    memset(vis, false, sizeof(vis));
}
void print(int p) //打印路径，一开始打反了。。。
{
    if (!pre[p])
        return;
    print(pre[p]);
    cout << pre[p] << "->";
}
void spfa() //标准的SPFA，不解释
{
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty())
    {
        int p = q.front();
        q.pop();
        vis[p] = false;

        for (int i = 2; i <= n + 1; i++)
        {
            if (map[p][i] && dis[i] < dis[p] + point[i])
            {
                dis[i] = dis[p] + point[i];
                pre[i] = p;
                if (!vis[i])
                {
                    q.push(i);
                    vis[i] = 1;
                }
            }
        }
    }
}

int main()
{
    cin >> t;
    while (t--)
    {
        init();
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> point[i];
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            map[u][v] = 1;
        }
        spfa();
        cout << "CASE " << cnt << "#" << endl;
        cnt++;
        cout << "points : " << dis[n + 1] << endl;
        cout << "circuit : ";
        print(n + 1);
        cout << 1 << endl; //切记最后还要回到1，换行也不能忘
        if (t)             //切记最后一行没有空行
            cout << endl;
    }

    return 0;
}
