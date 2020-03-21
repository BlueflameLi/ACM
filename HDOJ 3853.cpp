#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define maxn 1005
using namespace std;
struct node
{
	double p1, p2, p3;//p1是留在原地的概率，p2是向右走的概率,p3是向下走的概率
} map[maxn][maxn];
double dp[maxn][maxn];
int r, c;
int main()
{
	while (~scanf("%d%d", &r, &c))//多组数据
	{
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				scanf("%lf%lf%lf", &map[i][j].p1, &map[i][j].p2, &map[i][j].p3);//cin会TLE
		for (int i = r; i > 0; i--)
			for (int j = c; j > 0; j--)
			{
				if (i == r && j == c)//终点跳过
					continue;
				if (fabs(map[i][j].p1 - 1) < 0.0000001)//100%留在原地的直接跳过
					continue;
				dp[i][j] = (dp[i][j + 1] * map[i][j].p2 + dp[i + 1][j] * map[i][j].p3 + 2) / (1 - map[i][j].p1);
			}//dp[i][j]为从（i，j）到(r,c)的期望魔力消耗，dp[i][j]=map[i][j].p1*dp[i][j]+map[i][j].p2*dp[i][j+1]+map[i][j].p3*dp[i+1][j]+2
		printf("%.3lf\n", dp[1][1]);
	}
	return 0;
}