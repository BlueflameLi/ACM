#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
//#define int ll
#define rep(i, a, b) for (signed i = (a); i < (b); ++i)
#define per(i, a, b) for (signed i = (b)-1; i >= (a); --i)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define mem(a, b) memset(a, b, sizeof(a))
typedef long long ll;
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int LOGMAXN = 20;
int t;
int n, m;
map<string, int> mp; //mp将目录名映射成数字
struct edge
{
	int v;
	int next;
} e[MAXN];
int tot;
int dep[MAXN]; //深度
int head[MAXN];
int p[MAXN][LOGMAXN]; //p[i][j]表示节点i的第2^j的祖先(p[i][0]就是i的第一个祖先，即父亲)
inline void init()	  //初始化清空
{
	mem(e, 0);
	mem(p, 0);
	mem(dep, 0);
	mem(head, 0);
	mp.clear();
	tot = 0;
}
inline void add(int u, int v)
{
	e[++tot].v = v;
	e[tot].next = head[u];
	head[u] = tot;
}
void dfs(int u) //dfs遍历一遍算各点深度
{
	for (int i = head[u]; i; i = e[i].next)
	{
		dep[e[i].v] = dep[u] + 1;
		dfs(e[i].v);
	}
}
int lca(int a, int b) //找最近公共祖先
{
	if (dep[a] < dep[b]) //让a是更远的那个点
		swap(a, b);
	per(i, 0, LOGMAXN) if (dep[a] - (1 << i) >= dep[b]) a = p[a][i]; //先让两者跳到同一深度
	if (a == b)														 //b是a的祖先就直接返回b
		return a;
	per(i, 0, LOGMAXN) if (p[a][i] != p[b][i]) a = p[a][i], b = p[b][i]; //只要没有跳到公共的祖先，就两个点一起往上跳
	return p[a][0];														 //最后最近公共祖先就是他们的父亲
}
signed main()
{
	ios::sync_with_stdio(false); //关同步加速
	cin.tie(0);
	cout.tie(0);

	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		int cnt = 1;
		init();
		rep(i, 1, n)
		{
			string A, B;
			cin >> A >> B;
			if (!mp[A]) //字符串映射到数字
				mp[A] = cnt++;
			if (!mp[B])
				mp[B] = cnt++;
			add(mp[B], mp[A]);	 //建一条父亲指向儿子的边
			p[mp[A]][0] = mp[B]; //记录每个点的父亲是谁
		}
		rep(i, 1, n + 1) if (!p[i][0]) //找根节点，开始遍历求深度
		{
			dfs(i);
			break;
		}
		rep(j, 1, LOGMAXN) rep(i, 1, cnt) p[i][j] = p[p[i][j - 1]][j - 1]; //预处理，计算每个点的第2^j个祖先是谁

		rep(i, 0, m)
		{
			string A, B;
			cin >> A >> B;
			int a = mp[A];
			int b = mp[B];
			int c = lca(a, b);
			int ans = dep[a] - dep[c]; //先一次一次直到到最近公共祖先所在目录
			if (c != b)				   //如果b不是a的祖先，那么就再一次操作从公共祖先c跳到b
				ans++;
			cout << ans << endl;
		}
	}
	return 0;
}