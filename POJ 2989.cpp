#include <iostream>
#include <cstring>
#include <string>

using namespace std;
int n, m;
int ans;
bool map[150][150];     //存图
int some[150][150];     //预处理的点，可能可以加入团中的点（初始是所有点）
int all[150][150];      //已经加入当前团的点（初始空）
int none[150][150];     //之前团中的点（去重，初始空）

void dfs(int d, int an, int sn, int nn)
{
    if (sn == 0 && nn == 0)          //当some空了的时候到达终点
        ans++;                       //如果none不是空的，说明之前已经算过这个极大团

    int u = some[d][1];              //关键点pivot vertex u

    for (int i = 1; i <= sn; i++)
    {
        int v = some[d][i];

        if (map[u][v])              //对于一个极大团，要么包含u要么包含N-N(u)（即与u不相邻的）
            continue;               //所以搜索了u，就只需要找与u不相邻的，相邻的都已经和u一起搜索过了

        for (int j = 1; j <= an; j++)
            all[d + 1][j] = all[d][j];
        all[d + 1][an + 1] = v;     //将v加入团中

        int tsn = 0;
        for (int j = 1; j <= sn; j++)
            if (map[v][some[d][j]])     //取some ⋂= N(v)
                some[d + 1][++tsn] = some[d][j];

        int tnn = 0;
        for (int j = 1; j <= nn; j++)
            if (map[v][none[d][j]])     //取none ⋂= N(v)
                none[d + 1][++tnn] = none[d][j];

        dfs(d + 1, an + 1, tsn, tnn);   //往下搜

        some[d][i] = 0;             //将v从some中移到none中
        none[d][++nn] = v;

        if (ans > 1000)             //超过1000就不用算了
            return;
    }
}
int main()
{
    while (cin >> n >> m)
    {
        memset(map, false, sizeof(map));

        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            map[u][v] = map[v][u] = 1;
        }

        ans = 0;
        for (int i = 1; i <= n; i++)
            some[0][i] = i; //初始化，将所有点放进集合

        dfs(0, 0, n, 0);

        if (ans > 1000)
            cout << "Too many maximal sets of friends." << endl;
        else
            cout << ans << endl;
    }
    return 0;
}