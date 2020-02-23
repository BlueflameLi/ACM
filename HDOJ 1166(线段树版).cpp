#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 50005

using namespace std;

struct node
{
    int v;              //这题的单点修改，不需要lazy标记
    int l;
    int r;
} tree[maxn << 2];      //要开正常大小的四倍
int a[maxn];
int t;
int n;
int cnt;
void build_tree(int l, int r, int id)
{
    tree[id].l = l;
    tree[id].r = r;
    if (l == r)
    {
        tree[id].v = a[l];
        return;
    }
    int m = (l + r) >> 1;       //位运算速度更快
    build_tree(l, m, id << 1);
    build_tree(m + 1, r, id << 1 | 1);
    tree[id].v = tree[id << 1].v + tree[id << 1 | 1].v; //向上更新
}

int sum(int l, int r, int id)
{
    if (tree[id].l > r || tree[id].r < l)   //超出范围
        return 0;
    if (l <= tree[id].l && tree[id].r <= r)     //当前区间包含于查询区间，返回整个区间
        return tree[id].v;

    int m = (tree[id].l + tree[id].r) >> 1;
    return sum(l, r, id << 1) + sum(l, r, id << 1 | 1);
}
void update(int i, int v, int id)
{
    if (tree[id].l == tree[id].r)
    {
        tree[id].v += v;
        return;
    }

    int m = (tree[id].l + tree[id].r) >> 1;
    if (i <= m)
        update(i, v, id << 1);
    else
        update(i, v, id << 1 | 1);
    tree[id].v = tree[id << 1].v + tree[id << 1 | 1].v;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        cout << "Case " << ++cnt << ":" << endl;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]); //数据量较大用scanf
        build_tree(1, n, 1);
        string str;
        while (cin >> str)
        {
            if (str == "End")
                break;
            if (str == "Query")
            {
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%d\n", sum(l, r, 1));
            }
            else if (str == "Add")
            {
                int i, v;
                scanf("%d%d", &i, &v);
                update(i, v, 1);
            }
            else
            {
                int i, v;
                scanf("%d%d", &i, &v);
                update(i, -v, 1);
            }
        }
    }
    return 0;
}