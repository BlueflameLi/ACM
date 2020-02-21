#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int a[100005];      //树状数组的差分数组，a[i]表示原树状数组c[i]-c[i-1];
int n;
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int v)
{
    while (x <= n)
    {
        a[x] += v;
        x += lowbit(x);
    }
}
int sum(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += a[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    while (cin >> n && n)
    {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++)
        {
            int l, r;
            cin >> l >> r;
            add(l, 1);              //差分数组l点加1相当于原l之后的所有点加1
            add(r + 1, -1);         //r+1点减1，相当于原r+1点之后所有点减1，即实现[l,r]加1
        }
        cout << sum(1);
        for (int i = 2; i <= n; i++)
            cout << ' ' << sum(i);    //差分数组前缀和sum(i)就是原数组c[i]点的值
        cout << endl;
    }
    return 0;
}