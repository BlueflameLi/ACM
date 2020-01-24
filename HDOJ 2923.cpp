#include <iostream>
#include <queue>
#include <cstring>
#include <map>
#define inf 0x3f3f3f3f
using namespace std;

int n, c, r;
string e[1005];
int cnt;
int tot = 0;
int dis[200][200];
map<string, int> StoI; //通过map将地名编号，转化成int
void floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
            }
}
int main()
{
    while (cin >> n >> c >> r)
    {
        if (n == 0 && c == 0 && r == 0)
            break;
        tot++;
        cnt = 0;
        StoI.clear();
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i <= n; i++)
            dis[i][i] = 0;
        for (int i = 0; i <= c; i++)
        {
            cin >> e[i];
            if (!StoI.count(e[i]))
                StoI[e[i]] = ++cnt;
        }
        for (int i = 0; i < r; i++)
        {
            string u, w, v;
            cin >> u >> w >> v;
            if (!StoI.count(u))
                StoI[u] = ++cnt;
            if (!StoI.count(v))
                StoI[v] = ++cnt;
            int l = w.length();
            int x = 0;
            for (int j = 2; j < l - 2; j++)
                x = x * 10 + w[j] - '0';            //判重边
            if (dis[StoI[v]][StoI[u]] > x && w[0] == '<')
                dis[StoI[v]][StoI[u]] = x;
            if (dis[StoI[u]][StoI[v]] > x && w[l - 1] == '>')
                dis[StoI[u]][StoI[v]] = x;
        }
        floyd();
        int ans = 0;
        for (int i = 1; i <= c; i++)        //每次都要把车拖回来
            ans += dis[StoI[e[0]]][StoI[e[i]]]+dis[StoI[e[i]]][StoI[e[0]]];
        cout << tot << ". " << ans << endl;
    }
    return 0;
}