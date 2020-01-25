#include <iostream>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;

int map[105][105];
int f[1000000];
int a[105];
int t, n, m;
int u, v, w;
void Floyd()
{
    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
}

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        memset(f, inf, sizeof(f));              //因为是要油耗尽量小，所以初始赋无穷大
        cin >> n >> m;
        memset(map, 0x3f, sizeof(map));
        for (int i = 0; i <= n; i++)
            map[i][i] = 0;
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            if (map[u][v] > w)
                map[u][v] = map[v][u] = w;
        }
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum += a[i];                            //以总电力sum来作为背包容量
        }
        Floyd();
        f[0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = sum; j >= a[i]; j--)       //以到每个点的最短距离作为东西的价值
                f[j] = min(f[j], f[j - a[i]] + map[0][i]);  //这里是要价值也就是油耗尽可能小，所以是min
        int k = sum / 2 + 1;
        int ans = inf;
        for (int i = sum; i >= k; i--)
        {
            ans = min(ans, f[i]);
        }
        if (ans == inf)
            cout << "impossible" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}