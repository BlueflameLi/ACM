#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct node
{
    int id;   //id记录原位置
    int v;    //v记录值
} a[1000005]; //a数组用于离散化处理
int n;
int b[1000005];
bool cmp(node x, node y)
{
    return x.v < y.v;
}
int lowbit(int x)
{
    return x & -x;
}
int sum(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += b[x];
        x -= lowbit(x);
    }
    return ans;
}
void update(int x, int v)
{
    while (x <= n)
    {
        b[x] += v;
        x += lowbit(x);
    }
}
long long ans;
int main()
{
    while (cin >> n)
    {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].v;
            a[i].id = i;
        }
        sort(a + 1, a + n + 1, cmp); //按值大小排序
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            update(a[i].id, 1);      //按从小到大标记
            ans += i - sum(a[i].id); //如果b[i]到b[n]有n个标记，说明有n个比a[i].v小的数排在它后面
        }                            //全部加起来就总的逆序数
        cout << ans << endl;
    }
    return 0;
}