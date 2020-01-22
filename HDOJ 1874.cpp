#include <iostream>
#include <cstring>
#define inf 0x3f3f3f3f
#define maxn 1000 + 5
using namespace std;
int dis[maxn][maxn];
int n, m;
int a,b,x;
int s,t;
void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
    if (dis[s][t] == inf)
        cout<<-1<<endl;
    else
        cout<<dis[s][t]<<endl;
}
int main()
{
    while (cin >> n >> m)
    {
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < n; i++)
            dis[i][i] = 0;
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b >> x;
            if (x < dis[a][b])          //注意有重边
                dis[a][b] = dis[b][a] = x;
        }
        cin>>s>>t;
        floyd();
    }
    return 0;
}