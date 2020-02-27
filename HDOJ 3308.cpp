#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 100000 + 5
using namespace std;

struct node
{
    int l; //区间边界
    int r;
    int len;//区间长度
    int lmax;//以l开始的LCIS长度
    int rmax;//到r结束的LCIS长度
    int max;//区间[l,r]中LCIS长度

} tree[maxn << 2]; //要开四倍大小
int a[maxn];
int t, n, m;
int cnt;

void pushup(int p) //此题关键函数
{
    //这里就不解释了吧
    tree[p].lmax = tree[p << 1].lmax;
    tree[p].rmax = tree[p << 1 | 1].rmax;
    tree[p].max = max(tree[p << 1].max, tree[p << 1 | 1].max);

    int m = (tree[p].l + tree[p].r) >> 1;

    //判断中间连接部分是否可以合并
    if (a[m] < a[m + 1])
    {
        if (tree[p << 1].len == tree[p].lmax)   //如果左区间整段为LCIS
            tree[p].lmax += tree[p << 1 | 1].lmax;//那么合并后就需要更新lmax
        if (tree[p << 1 | 1].len == tree[p].rmax)//同理右区间整段为LCIS的话也是一样
            tree[p].rmax += tree[p << 1].rmax;

        //合并后产生更长的CIS的话就更新
        tree[p].max = max(tree[p].max, tree[p << 1].rmax + tree[p << 1 | 1].lmax);
    }
    // cout << tree[p].l << ' ' << tree[p].r << ' ' << tree[p].lmax << ' ' << tree[p].rmax << ' ' << tree[p].max << endl;
    //调试用
}
void build(int l, int r, int p)
{
    tree[p].l = l; //初始化
    tree[p].r = r;
    tree[p].len = r - l + 1;
    if (l == r)
    {
        //只有一个点的话，LCIS长度肯定是1
        tree[p].max = tree[p].lmax = tree[p].rmax = 1;
        return;
    }

    int m = (l + r) >> 1;

    build(l, m, p << 1);
    build(m + 1, r, p << 1 | 1);

    pushup(p);
}

void update(int x, int v, int p)
{
    if (tree[p].l == tree[p].r)
    {
        a[x] = v;//这句放在主函数也行，可以让这个函数少一个形参
        return;
    }

    int m = (tree[p].l + tree[p].r) >> 1;

    if (x <= m)
        update(x, v, p << 1);
    else
        update(x, v, p << 1 | 1);
    pushup(p); //向上更新
}
int query(int l, int r, int p)
{
    if (tree[p].r < l || r < tree[p].l)
        return 0;
    if (l <= tree[p].l && tree[p].r <= r)
        return tree[p].max;

    int m = (tree[p].l + tree[p].r) >> 1;

    //这里lmax和rmax和tree里的意思不一样，这里分别代表左区间和右区间的LCIS长度
    int lmax = query(l, r, p << 1);
    int rmax = query(l, r, p << 1 | 1);

    //如果查询区间是完整的话，可以直接返回
    if (r <= m)     
        return lmax;
    if (m < l)
        return rmax;
    
    //查询区间是被分隔开的话，还要再看看能不能合并
    int ans = max(lmax, rmax);//不能合并的话就是左右区间的LCIS中更大的那个
    if (a[m] < a[m + 1])//这里容易理解的吧
        ans = max(ans, min(tree[p << 1].rmax, m - l + 1) + min(tree[p << 1 | 1].lmax, r - m));

    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        build(1, n, 1);

        while (m--)
        {
            char c;
            int x, y;
            cin >> c >> x >> y;
            if (c == 'U')
                update(x + 1, y, 1);//数据的编号是从0开始的，线段树是从1开始的，所以要加1
            else if (c == 'Q')
                cout << query(x + 1, y + 1, 1) << endl;//同理编号加1
            // else     //调试用
            //     cout << "Wrong!!!" << endl;
        }
    }
    return 0;
}