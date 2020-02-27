#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 100000 + 5
using namespace std;

struct node
{
    int v;      //区间和
    int l;      //区间边界
    int r;
    int len;    //区间长度
    int lazy;   //延迟标记
} tree[maxn << 2];//要开四倍大小

int t, n, q;
int cnt;

void pushup(int p)//子节点更新完，向上更新父节点
{
    tree[p].v = tree[p << 1].v + tree[p << 1 | 1].v;
}
void build(int l, int r, int p)
{
    tree[p].l = l;      //初始化
    tree[p].r = r;
    tree[p].len = r - l + 1;
    tree[p].lazy = 0;

    if (l == r)
    {
        tree[p].v = 1;  //初始为铜
        return;
    }

    int m = (l + r) >> 1;

    build(l, m, p << 1);
    build(m + 1, r, p << 1 | 1);

    pushup(p);          //切记向上更新
}
void pushdown(int p)//将延迟标记推下去
{
    if (tree[p].lazy)
    {
        tree[p << 1].v = tree[p].lazy * tree[p << 1].len;//更新子节点
        tree[p << 1 | 1].v = tree[p].lazy * tree[p << 1 | 1].len;

        tree[p << 1].lazy = tree[p << 1 | 1].lazy = tree[p].lazy; //延迟标记推下去
        tree[p].lazy = 0;           //记得去掉当前节点的延迟标记
    }
}
void update(int l, int r, int z, int p)
{
    if (l <= tree[p].l && tree[p].r <= r)   //若当前区间包含于查询区间
    {
        tree[p].v = z * tree[p].len;        //更新区间和和延迟标记
        tree[p].lazy = z;
        return;
    }

    pushdown(p);    //先将延迟标记推下去，更新子节点

    int m = (tree[p].l + tree[p].r) >> 1;

    if (l <= m)
        update(l, r, z, p << 1);
    if (r > m)
        update(l, r, z, p << 1 | 1);
    pushup(p);      //向上更新
}

int main()
{
    ios::sync_with_stdio(false);//数据较大，用scanf或者关同步
    cout.tie(NULL);
    cin >> t;
    while (t--)
    {
        cin >> n;
        build(1, n, 1);

        cin >> q;
        while (q--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            update(x, y, z, 1);
        }
        //因为输出整段的和，所以不许要另外的函数了，直接输出即可
        cout << "Case " << ++cnt << ": The total value of the hook is " << tree[1].v << "." << endl;
    }
    return 0;
}