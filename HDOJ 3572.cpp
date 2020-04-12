#include <iostream>
#include <cstring>
#include <queue>
#define maxn 1005
#define maxm 250005
#define inf 0x3f3f3f3f
using namespace std;
int T;
int n, m;
struct edge
{
      int v;
      int c;
      int next;
} e[maxm << 1];
int tot;
int cnt;
int head[maxn];
int cur[maxn];
void add(int u, int v, int c)
{
      e[++tot].v = v;
      e[tot].c = c;
      e[tot].next = head[u];
      head[u] = tot;
}
int dep[maxn];
bool bfs(int s, int t)
{
      queue<int> q;
      memset(dep, 0, sizeof(dep));
      dep[s] = 1;
      q.push(s);
      for (int i = 0; i <= t; i++) //总的点数不是n，而是t+1
            cur[i] = head[i];
      while (!q.empty())
      {
            s = q.front();
            q.pop();
            for (int i = head[s]; ~i; i = e[i].next)
                  if (e[i].c && !dep[e[i].v])
                  {
                        dep[e[i].v] = dep[s] + 1;
                        if (e[i].v == t)
                              return true;
                        q.push(e[i].v);
                  }
      }
      return false;
}
int dfs(int s, int t, int flow)
{
      if (s == t || !flow)
            return flow;
      int ans = 0;
      for (int &i = cur[s]; ~i; i = e[i].next)
            if (e[i].c && dep[e[i].v] == dep[s] + 1)
            {
                  int res = dfs(e[i].v, t, min(flow, e[i].c));
                  if (!res)
                        dep[e[i].v] = 0;
                  e[i].c -= res;
                  e[i ^ 1].c += res;
                  ans += res;
                  flow -= res;
                  if (!flow)
                        break;
            }
      return ans;
}
void init()
{
      memset(e, -1, sizeof(e));
      memset(head, -1, sizeof(head));
      tot = -1;
}
int dinic(int s, int t)
{
      int ans = 0;
      while (bfs(s, t))
            ans += dfs(s, t, inf);
      return ans;
}
int main()
{
      cin >> T;
      while (T--)
      {
            init();
            cin >> n >> m;
            int sum = 0;
            int maxd = 0;
            int s = 0;
            for (int i = 1; i <= n; i++)
            {
                  int pi, si, ei;
                  cin >> pi >> si >> ei;
                  sum += pi;            //记录源点流出的最大流量，即每个任务完成所需时间的累加
                  maxd = max(ei, maxd); //记录最晚的那一天
                  add(s, i, pi);        //超级源点到每个任务的流量为任务所需时间pi
                  add(i, s, 0);         //反悔边
                  for (int j = si; j <= ei; j++)
                  {
                        add(i, j + n, 1); //每个任务和其开始到结束的每一天连起来，容量为1
                        add(j + n, i, 0); //因为做一天只能算一天的任务，不能一天把pi天的都做完
                  }
            }
            int t = maxd + n + 1; //超级汇点
            for (int i = n + 1; i < t; i++)
            {
                  add(i, t, m); //每一天到汇点的容量为m
                  add(t, i, 0); //因为每天只能同时有m个机器工作
            }
            if (dinic(s, t) == sum) //如果每个任务都干满了pi天，那就说明完成了
                  cout << "Case " << ++cnt << ": Yes" << endl;
            else
                  cout << "Case " << ++cnt << ": No" << endl;
            if (t)
                  cout << endl;
      }
      return 0;
}
