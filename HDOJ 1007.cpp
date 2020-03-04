#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 100005
#define inf 0x3f3f3f3f
using namespace std;
int n;
struct node
{
	double x, y;
} a[maxn];
node tmp[maxn];
bool cmp1(node x, node y)//按x排序
{
	if (x.x == y.x)
		return x.y < y.y;
	return x.x < y.x;
}
bool cmp2(node x, node y)//按y排序
{
	if (x.y == y.y)
		return x.x < y.x;
	return x.y < y.y;
}
double dis(node x, node y)//计算距离
{
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
double find(int l, int r)
{
	if (l == r)			//一个点算不了，返回无穷大
		return inf;
	if (r - l == 1)		//两个点，那最小距离就是两点间的距离
		return dis(a[l], a[r]);
	int m = (l + r) >> 1;//二分，先在左右区间分别找区间内最近两点的距离
	//有两种情况，第一种，最近的两点都在左区间或都在右区间，第二种，一个在左区间，一个在右区间
	double d = min(find(l, m), find(m + 1, r));	//第一种情况的话，这就是答案了，下面是讨论第二种情况
	int t = 0;
	for (int i = l; i <= r; i++)
		if (fabs(a[i].x - a[m].x) <= d)	//如果到m的横坐标距离都大于d的，两点间的距离就更大于d了
			tmp[t++] = a[i];
	sort(tmp, tmp + t, cmp2);//将这些可能的点按y排序
	for (int i = 0; i < t; i++)
		for (int j = i + 1; j < t; j++)
		{
			if (tmp[j].y - tmp[i].y > d)//同理纵坐标差都超过d了的，后面的显然距离更大了，直接退出
				break;
			d = min(d, dis(tmp[i], tmp[j]));//挨个比较，看看有没有更近的两个点。
		}
	return d;
}
int main()
{
	while (~scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		sort(a, a + n, cmp1);	//按x排序，分治
		printf("%.2lf\n", find(0, n - 1) / 2);//答案就是最近点距离的一半
	}
	return 0;
}