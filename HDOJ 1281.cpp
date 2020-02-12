#include <iostream>
#include <cstring>

using namespace std;
int n, m, k;
int linker[150];
bool map[150][150];
bool vis[150];
int cnt;
int ans1, ans2;
int tot;
bool dfs(int u)
{
    for (int i = 1; i <= n; i++)
        if (map[u][i] && !vis[i])
        {
            vis[i] = 1;
            if (linker[i] == -1 || dfs(linker[i])) //如果i没有对象或者i的对象还能找到其他对象
            {                                      //那么u和i就匹配
                linker[i] = u;
                return true;
            }
        }
    return false;
}
void hungary()
{
    cnt = 0;
    memset(linker, -1, sizeof(linker));
    for (int i = 1; i <= n; i++)
    {
        memset(vis, false, sizeof(vis)); //因为别人找过的对象你也还可以去试试，所以每次都要清空
        if (dfs(i))                      //如果i能找到对象，匹配数++
            cnt++;
    }
}
int main()
{
    while (cin >> n >> m >> k)
    {
        memset(map, false, sizeof(map));
        for (int i = 0; i < k; i++)
        {
            int u, v;
            cin >> u >> v;              //转化成二分图
            map[u][v] = 1;
        }
        hungary();
        ans1 = cnt;                     //ans1最大匹配数，即最多能放的车
        ans2 = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                if (map[i][j])
                {
                    map[i][j] = 0;      //若某格子不放车
                    hungary();
                    if (cnt < ans1)     //最大匹配数变小了
                        ans2++;         //说明是重要点
                    map[i][j] = 1;
                }
            }
        cout << "Board " << ++tot << " have " << ans2 << " important blanks for " << ans1 << " chessmen." << endl;
    }
}