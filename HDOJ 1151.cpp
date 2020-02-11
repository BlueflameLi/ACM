#include <iostream>
#include <cstring>

using namespace std;
int t, n, m, k;
int linker[150];
bool map[150][150];
bool vis[150];
int cnt;

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
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        memset(map, false, sizeof(map));
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;              //构造二分图，起点是1~n，终点是1'~n'
            map[u][v] = 1;
        }

        hungary();
        cout << n - cnt << endl;        //最小路径覆盖数等于顶点数-最大匹配数
    }
}