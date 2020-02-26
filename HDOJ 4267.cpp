#include <iostream>
#include <cstring>
#define maxn 50005

using namespace std;

struct node
{
    int v[55]; //k属于[1,10],有十种情况，a%k属于[0,k-1],有k种情况，总共11*10/2=55种情况
    int l;     //二维数组可能MLE,所以用一维
    int r;
} tree[maxn << 2];
int a[maxn];
int n;
void build_tree(int l, int r, int id)
{
    tree[id].l = l;
    tree[id].r = r;
    memset(tree[id].v, 0, sizeof(tree[id].v));
    if (l == r)
        return;
    int m = (l + r) >> 1;
    build_tree(l, m, id << 1);
    build_tree(m + 1, r, id << 1 | 1);
}
void update(int l, int r, int id, int u, int k, int v)
{
    if (l <= tree[id].l && tree[id].r <= r)
    {
        int t = k * (k - 1) / 2 + u; //计算出k==k,a%k==u是第几种情况
        tree[id].v[t] += v;
        return;
    }

    int m = (tree[id].l + tree[id].r) >> 1;
    if (l <= m)
        update(l, r, id << 1, u, k, v);
    if (r > m)
        update(l, r, id << 1 | 1, u, k, v);
}
int query(int x, int id)
{
    if (tree[id].l > x || tree[id].r < x)
        return 0;
    int ans = 0;
    for (int i = 1; i <= 10; i++)
    {
        int t = i * (i - 1) / 2 + x % i;    //(i-a)%k==0 等价于i%k==a%k，把符合要求的都加上
        if (tree[id].v[t])
            ans += tree[id].v[t];
    }

    if (tree[id].l == tree[id].r)
        return ans;

    int m = (tree[id].l + tree[id].r) >> 1;
    return ans + query(x, id << 1) + query(x, id << 1 | 1);
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);     //数据量很大，要scanf
        build_tree(1, n, 1);
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++)
        {
            int d;
            scanf("%d", &d);
            if (d == 1)
            {
                int l, r, k, c;
                scanf("%d%d%d%d", &l, &r, &k, &c);
                update(l, r, 1, l % k, k, c);
            }
            else
            {
                int x;
                scanf("%d", &x);
                printf("%d\n", query(x, 1) + a[x]);
            }
        }
    }
    return 0;
}