#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

int t, n, a[50005];
int cnt;
int lowbit(int x)       //取x的最低位的1，利用了负数补码的性质
{
    return x & -x;
}
void update(int x, int v)   //更新x节点的值
{
    while (x <= n)
    {
        a[x] += v;
        x += lowbit(x);
    }
}
int sum(int x)      //x的前缀和
{
    int ans = 0;
    while (x)
    {
        ans += a[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    cin >> t;
    while (t--)
    {
        memset(a, 0, sizeof(a));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            update(i, x);       //初始都是0，直接加上去就行了，不需要另外建
        }
        cout << "Case " << ++cnt << ":" << endl;
        string str;
        while (cin >> str)
        {
            if (str == "End")
                break;
            if (str == "Query")
            {
                int l, r;
                cin >> l >> r;
                cout << sum(r) - sum(l - 1) << endl;        //l到r的和就是r的前缀和减去l-1的前缀和
            }
            else if (str == "Add")
            {
                int i, j;
                cin >> i >> j;
                update(i, j);
            }
            else if (str == "Sub")
            {
                int i, j;
                cin >> i >> j;
                update(i, -j);          //减去只要加上一个负数即可
            }
        }
    }
    return 0;
}
