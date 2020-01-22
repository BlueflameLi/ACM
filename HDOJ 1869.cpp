#include <iostream>
#include <cstring>
#define inf 0x3f3f3f3f      //这个无穷大很巧妙
using namespace std;
int n, m, u, v;
int map[105][105];
void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
}
int main()
{

    while (cin >> n >> m)
    {                                   //memset会将内存填满0x3f
        memset(map, 0x3f, sizeof(map)); //这样每一个元素都是0x3f3f3f3f了
        for (int i = 0; i < n; i++)
            map[i][i] = 0;
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v;
            map[u][v] = map[v][u] = 1;
        }
        floyd();
        int flag = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (map[i][j] > 7)      //中间隔6个就是距离7
                {
                    flag = 1;
                    j = n;
                    i = n;
                }
        if (flag)
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }
    return 0;
}
