#include <iostream>
#include <cstring>
#include <queue>
#define maxn 20
#define maxm 1005
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
      for (int i = 1; i <= n; i++)
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
            for (int i = 0; i < m; i++)
            {
                  int u, v, c;
                  cin >> u >> v >> c;
                  add(u, v, c);
                  add(v, u, 0);
            }
            cout << "Case " << ++cnt << ": " << dinic(1, n) << endl;
      }
      return 0;
}