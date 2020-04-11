#include <iostream>
#include <cstring>
#include <queue>
#define maxn 205
#define inf 0x3f3f3f3f
using namespace std;
int n, m; //n是点数,m是边数
struct edge
{
	int v, w, next;
} e[maxn << 1]; //有反向边，要双倍
int tot;
int head[maxn];
int cur[maxn]; //当前弧优化，记录当前的弧
void add(int u, int v, int w)
{
	e[++tot].v = v;
	e[tot].w = w; //w是权重，即该边的容量
	e[tot].next = head[u];
	head[u] = tot;
}
int dep[maxn]; //存当前点的深度
void init()
{
	memset(e, -1, sizeof(e));
	memset(head, -1, sizeof(head));
	tot = -1;
}
bool bfs(int s, int t)
{
	memset(dep, 0, sizeof(dep));
	queue<int> q;
	q.push(s);
	dep[s] = 1;					 //源点
	for (int i = 1; i <= n; i++) //当前弧优化，拷贝一份head
		cur[i] = head[i];
	while (!q.empty())
	{
		s = q.front();
		q.pop();
		for (int i = head[s]; ~i; i = e[i].next)
		{
			if (e[i].w > 0 && !dep[e[i].v]) //容量为0的边流不过去，已经流过的也不流了
			{
				dep[e[i].v] = dep[s] + 1;
				if (e[i].v == t) //到终点就可以结束了，和终点同一层或更深层的我们是不会流到汇点的，所以不用管
					return true;
				q.push(e[i].v);
			}
		}
	}
	return false; //汇点都流不到，肯定无法增广了
}
int dfs(int s, int t, int flow) //s为当前点,t为汇点,flow是流入当前点的剩余流量
{
	if (s == t || !flow) //流入汇点的流量就是该条路的流量，剩余流量没了，也结束
		return flow;
	int ans = 0;
	for (int &i = cur[s]; ~i; i = e[i].next) //当前弧优化，&是引用，i就相当于就是cur[s]的别名，改i和改cur[s]是一样的
	{
		if (e[i].w && dep[e[i].v] == dep[s] + 1) //如果该点能流到儿子节点，且儿子节点是该点的下一层深度的
		{
			int res = dfs(e[i].v, t, min(flow, e[i].w)); //那就继续往下流
			if (!res)
				dep[e[i].v] = 0; //如果这条路死了，那下次就不往这条路流了
			e[i].w -= res;		 //这条路的容量减小
			e[i ^ 1].w += res;	 //i^1，在这里等价于i+1，反悔边容量增加
			ans += res;			 //答案增加
			flow -= res;		 //剩余流量减小
			if (!flow)			 //流量用完了返回
				break;
		}
	}
	return ans;
}

int dinic(int s, int t)
{
	int ans = 0;
	while (bfs(s, t))		   //每次都先bfs建分层图
		ans += dfs(s, t, inf); //然后dfs找增广路
	return ans;
}
int main()
{
	while (cin >> m >> n)
	{
		init(); //初始化
		for (int i = 0; i < m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			add(u, v, w);
			add(v, u, 0); //建立反悔边
		}
		cout << dinic(1, n) << endl;
	}
	return 0;
}
