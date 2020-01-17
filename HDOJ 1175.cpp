#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int n, m,t;
int a1, b1, a2, b2;					//因为y1之类的变量名有时候会函数冲突，所以我干脆改成了a1,b1这种
int dx[4] = { 1,0,-1,0 };			//方向
int dy[4] = { 0,1,0,-1 };
int map[1005][1005];
int v[1005][1005];					//线肯定不会交叉，标记一下，避免重复
struct node
{
	int x, y;
	int turn;					//记录转弯次数
}s;								//s是起始点
bool check(node p)				//判断是否越界，是否有棋子挡住（除终点棋子）
{
	if (p.x <= 0 || p.y <= 0)
		return false;
	if (p.x > n || p.y > m)
		return false;
	if(!map[p.x][p.y])
		return true;
	if (p.x == a2 && p.y == b2)
		return true;
	return false;
}
void bfs()
{
	queue<node>q;
	node p, e;
	memset(v, 0, sizeof(v));	//清空，别忘了头文件，vs不加cstring也能运行，我经常忘。。。
	s.turn = -1;				//起点往任意方向都没有转弯
	q.push(s);					//起点入队，初始化要在入队前做
	v[s.x][s.y] = 1;
	
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		//cout << p.x << ' ' << p.y << ' ' << p.turn << endl;
		if (p.turn >= 2) continue;	//转弯次数超了的，直接过
		for (int i = 0; i < 4; i++)
		{
			e.x = p.x + dx[i];
			e.y = p.y + dy[i];
			e.turn = p.turn + 1;
			//cout <<p.x<<' '<<p.y<<' '<< e.x << ' ' << e.y << endl;
			while (check(e))		//因为只能拐两次，所以一直往一个方向冲就行了
			{
				
				if (e.x == a2 && e.y == b2)
				{
					cout << "YES" << endl;
					return;
				}
				if (!v[e.x][e.y])
				{
					v[e.x][e.y] = 1;
					q.push(e);
					
				}
				e.x +=  dx[i];
				e.y +=  dy[i];	//继续再这个方向上冲

			}
		}
	}
	cout << "NO" << endl;
}
int main()
{
	while (cin >> n >> m)
	{
		if (!n && !m)
			break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> map[i][j];
		cin >> t;
		while (t--)
		{
			cin >> a1 >> b1 >> a2 >> b2;
			if(a1==a2&&b1==b2)
			{
				cout << "NO" << endl;			//起点终点重合的不行
				continue;
			}
			if (a1>n||a2>n||b1>m||b2>m)			//越界的不行（因为已经正整数所以只要看一边就行了）
			{
				cout << "NO" << endl;
				continue;
			}
			if (map[a1][b1] != map[a2][b2])		//棋子要相同的
			{
				cout << "NO" << endl;
				continue;
			}
			if (map[a1][b1] * map[a2][b2] == 0)	//总得有棋子吧
			{
				cout << "NO" << endl;
				continue;
			}
			s.x = a1;
			s.y = b1;
			bfs();
		}
	}
	return 0;
}