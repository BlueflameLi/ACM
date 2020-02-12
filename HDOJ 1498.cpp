#include <iostream>
#include <cstring>

using namespace std;
int n, m, k;
int linker[150];
int map[150][150];
bool vis[150];
int cnt;
bool v[150];
bool dfs(int u, int color)
{
    for (int i = 0; i < n; i++)
        if (map[u][i] == color && !vis[i])
        {
            vis[i] = 1;
            if (linker[i] == -1 || dfs(linker[i], color)) //如果i没有对象或者i的对象还能找到其他对象
            {                                             //那么u和i就匹配
                linker[i] = u;
                return true;
            }
        }
    return false;
}
void hungary(int color)
{
    cnt = 0;
    memset(linker, -1, sizeof(linker));
    for (int i = 0; i < n; i++)
    {
        memset(vis, false, sizeof(vis)); //因为别人找过的对象你也还可以去试试，所以每次都要清空
        if (dfs(i, color))               //如果i能找到对象，匹配数++
            cnt++;
    }
}
int main()
{
    while (cin >> n >> k && n && k)
    {
        memset(map, 0, sizeof(map));
        memset(v, false, sizeof(v));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                v[map[i][j]] = 1;       //标记一下有哪些颜色
            }
        bool flag = 0;
        for (int i = 1; i <= 50; i++)
            if (v[i])
            {
                hungary(i);
                if (cnt > k)           //最大匹配数cnt就是把气球弄爆所需的最少次数
                {
                    if (flag)
                        cout << ' ' << i;
                    else
                    {
                        flag = 1;
                        cout << i;
                    }
                }
            }
        if (!flag)
            cout << -1;
        cout << endl;
    }
}