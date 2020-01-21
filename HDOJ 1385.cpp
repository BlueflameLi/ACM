
#include <iostream>
#include <algorithm>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;
int dis[1000][1000];
int tax[1000];
int path[1000][1000];
int n, m, u, v;
void floyd()            //字典序最好还是用floyd，当然其他也不是不行
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dis[i][j] >= dis[i][k] + dis[k][j] + tax[k])
                {
                    if (dis[i][j] == dis[i][k] + dis[k][j] + tax[k] && path[i][j] <= path[i][k])
                        continue;
                    dis[i][j] = dis[i][k] + dis[k][j] + tax[k];
                    path[i][j] = path[i][k];
                }
}
int main()
{
    while (cin >> n && n)                   //多组数据的
    {
        memset(path, 0, sizeof(path));      //path要清空
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> dis[i][j];
                if (dis[i][j] == -1)        //没有路的赋无穷大
                    dis[i][j] = inf;
                path[i][j] = j;
            }
        for (int i = 1; i <= n; i++)
            cin >> tax[i];
        floyd();
        while (cin >> u >> v && u != -1 && v != -1)
        {
            cout << "From " << u << " to " << v << " :" << endl;
            cout << "Path: " << u;
            int p = u;
            while (p != v)
            {
                cout << "-->" << path[p][v];
                p = path[p][v];
            }
            cout << endl                    //别忘了这一堆换行
                 << "Total cost : " << dis[u][v] << endl
                 << endl;
        }
    }
    return 0;
}
