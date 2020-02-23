#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 200005

using namespace std;

struct node
{
    int v;
    int l;
    int r;
} tree[maxn << 2];
int a[maxn];
int n, m;
void build_tree(int l, int r, int id)
{
    tree[id].l = l;
    tree[id].r = r;
    if (l == r)
    {
        tree[id].v = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build_tree(l, m, id << 1);
    build_tree(m + 1, r, id << 1 | 1);
    tree[id].v = max(tree[id << 1].v, tree[id << 1 | 1].v);
}

int query(int l, int r, int id)
{
    if (tree[id].l > r || tree[id].r < l)
        return 0;
    if (l <= tree[id].l && tree[id].r <= r)
        return tree[id].v;

    int m = (tree[id].l + tree[id].r) >> 1;
    return max(query(l, r, id << 1), query(l, r, id << 1 | 1));
}
void update(int i, int v, int id)
{
    if (tree[id].l == tree[id].r)
    {
        tree[id].v = v;     //因为是修改所以直接赋值
        return;
    }

    int m = (tree[id].l + tree[id].r) >> 1;
    if (i <= m)
        update(i, v, id << 1);
    else
        update(i, v, id << 1 | 1);
    tree[id].v = max(tree[id << 1].v, tree[id << 1 | 1].v);
}
int main()
{
    while (~scanf("%d%d", &n, &m))  //多组数据
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);         //数据较大用scanf
        getchar();      //两个getchar()把回车吃了
        build_tree(1, n, 1);
        for (int i = 0; i < m; i++)
        {
            char c;
            int b, d;
            scanf("%c%d%d", &c, &b, &d);
            getchar();
            if (c == 'Q')
                printf("%d\n", query(b, d, 1));
            else if (c == 'U')
                update(b, d, 1);
        }
    }
    return 0;
}