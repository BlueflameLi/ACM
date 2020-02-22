#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int t;
int cnt;
int a[1005][1005];  //二维树状数组
int b[1005][1005];  //普通数组，存每个点的书的数量
int n;
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int y, int v)
{
    int j;
    b[x][y] += v;
    while (x < 1005)
    {
        j = y;
        while (j < 1005)
        {
            a[x][j] += v;
            j += lowbit(j);
        }
        x += lowbit(x);
    }
}
int sub(int x, int y, int v)
{
    if (b[x][y] < v)    //如果超过原有的书，就搬完原有的书
        v = b[x][y];
    b[x][y] -= v;
    int j;
    while (x < 1005)
    {
        j = y;
        while (j < 1005)
        {
            a[x][j] -= v;
            j += lowbit(j);
        }
        x += lowbit(x);
    }
    return v;       //返回实际搬运的书的数量
}
int sum1(int x, int y) //sum1(x,y)为以(1,1)-(x,y)为对角线的矩阵的元素和
{
    int ans = 0;
    int j;
    while (x > 0)
    {
        j = y;
        while (j > 0)
        {
            ans += a[x][j];
            j -= lowbit(j);
        }
        x -= lowbit(x);
    }
    return ans;
}
int sum2(int x1, int y1, int x2, int y2)
{
    if (x1 > x2)
        swap(x1, x2); //点(x1,y1)不一定在(x2,y2)的左上角，所以要交换一下
    if (y1 > y2)
        swap(y1, y2);
    return sum1(x2, y2) - sum1(x2, y1 - 1) - sum1(x1 - 1, y2) + sum1(x1 - 1, y1 - 1);
}
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        memset(a, 0, sizeof(a));
        for (int i = 1; i < 1005; i++)  //树状数组最好从1开始，否则会大大降低效率
            for (int j = 1; j < 1005; j++)
            {
                add(i, j, 1);
                b[i][j] = 1;
            }
        cout << "Case " << ++cnt << ":" << endl;
        for (int i = 0; i < n; i++)
        {
            char c;
            cin >> c;
            if (c == 'S')
            {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                x1++;       //因为数据是有(0,0)点，所以所有坐标加1
                y1++;
                x2++;
                y2++;
                cout << sum2(x1, y1, x2, y2) << endl;
            }
            else if (c == 'A')
            {
                int x, y, v;
                cin >> x >> y >> v;
                x++;
                y++;
                add(x, y, v);
            }
            else if (c == 'D')
            {
                int x, y, v;
                cin >> x >> y >> v;
                x++;
                y++;
                sub(x, y, v);
            }
            else
            {
                int x1, y1, x2, y2, v;
                cin >> x1 >> y1 >> x2 >> y2 >> v;
                x1++;
                y1++;
                x2++;
                y2++;
                v = sub(x1, y1, v);
                add(x2, y2, v);
            }
        }
    }
    return 0;
}