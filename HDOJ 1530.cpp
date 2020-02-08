#include <iostream>
#include <cstdio>
using namespace std;

int n;
int map[55][55];            //存图
int vis[55];                //记录，目前已经取了的点
int cnt[55];                //cnt[i]表示从i到n中最大团的大小
int maxn;                   //最大团的大小
bool dfs(int u, int now)    //now表示当前已选的点的个数
{
    for (int i = u + 1; i <= n; i++)
    {
        if (cnt[i] + now <= maxn)       //剪枝，如果之前的最大团加上现在选的点还是比最优解小，那么就return
            return false;
        if (map[u][i])
        {
            int j;
            for (j = 0; j < now; j++)
                if (!map[i][vis[j]])    //判断i是否和当前团中元素都相邻
                    break;
            if (j == now)
            {
                vis[now] = i;           //是的话，入团
                if (dfs(i, now + 1))    //往下继续选点
                    return true;
            }
        }
    }
    if (now > maxn)         //更新答案，如果要输出最大团中有哪些点的话，在这里存答案，这题没有
    {
        maxn = now;
        return true;        //每存一个点，最大团大小最多加1，所以后面不需要再搜索了
    }
    return false;
}
void maxClique()
{
    maxn = -1;
    for (int i = n; i > 0; i--)     //因为cnt表示i到n中最大团大小，所以要从n开始倒着遍历。
    {
        vis[0] = i;
        dfs(i, 1);
        cnt[i] = maxn;
    }
}
int main()
{
    while (cin >> n && n)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &map[i][j]);
        maxClique();
        printf("%d\n", maxn);
    }
    return 0;
}