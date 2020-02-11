#include <iostream>
#include <cstring>

using namespace std;
int n, m, k;
int linker[105];
bool map[105][105];
bool vis[105];
int cnt;

bool dfs(int u)
{
    for (int i = 1; i < m; i++)
        if (map[u][i] && !vis[i])
        {
            vis[i] = 1;
            if (linker[i] == -1 || dfs(linker[i]))   //如果i没有对象或者i的对象还能找到其他对象
            {                                        //那么u和i就匹配
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
    for (int i = 1; i < n; i++)
    {
        memset(vis, false, sizeof(vis));   //因为别人找过的对象你也还可以去试试，所以每次都要清空
        if (dfs(i))         //如果i能找到对象，匹配数++
            cnt++;
    }
}
int main()
{
    while (cin >> n && n)
    {
        cin >> m >> k;
        memset(map, false, sizeof(map));
        for (int i = 0; i < k; i++)
        {
            int id, u, v;
            cin >> id >> u >> v;
            if (u && v)       //一开始A和B都在mode_0，所以所有mode_0能完成的任务都不用管
                map[u][v] = 1;
        }

        hungary();
        cout << cnt << endl;
    }
}