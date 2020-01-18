#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int n, m;
int dx[4] = { 0,1,0,-1 };			//dx和dy两个数组控制方向
int dy[4] = { 1,0,-1,0 };
char map[25][25];					//将迷宫的地图存下来
int v[25][25];						//标记走过的路
struct node
{
	int x, y;						//x和y是坐标
	int time;						//时间
}s;									//s是起始点
bool check(node p)
{
	if (p.x < 0 || p.y < 0)			//判断是否越界
		return false;
	if (p.x >= n || p.y >= m)
		return false;
	if (map[p.x][p.y] == '*')		//是否是障碍
		return false;
	if (v[p.x][p.y])				//是否走过
		return false;
	return true;
}
void bfs()
{
	queue<node> q;
	q.push(s);						//将起始点入队
	node next, p;
	v[s.x][s.y] = 1;
	while (!q.empty())
	{
		p = q.front();				//队首是p
		q.pop();					//出队
		if (map[p.x][p.y] == 'T')			//到终点了，输出时间，退出
		{
			cout << p.time << endl;
			return;
		}
		//cout << p.x << ' ' << p.y << endl;
		for (int i = 0; i < 4; i++)
		{
			next.x = p.x + dx[i];	//计算下一个点next的坐标
			next.y = p.y + dy[i];
			//cout << next.x <<' '<< next.y<<endl;
			if (check(next))
			{
				
				if (map[next.x][next.y] == '|')	//遇到楼梯
				{
					next.x += dx[i];		//先看看楼梯对面是什么
					next.y += dy[i];
					if (!check(next)) continue;
					if (i % 2 && p.time % 2 == 0 || i % 2 == 0 && p.time % 2)
					{
						v[next.x][next.y] = 1;
						next.time = p.time + 1;
						q.push(next);
					}
					else
					{
						p.time++;				//走不了的，停留
						q.push(p);
					}
				}
				else if (map[next.x][next.y] == '-')	//同上，不解释
				{
					next.x += dx[i];
					next.y += dy[i];
					if (!check(next)) continue;
					if (i % 2 && p.time % 2 || i % 2 == 0 && p.time  % 2==0)
					{
						v[next.x][next.y] = 1;
						next.time = p.time + 1;
						q.push(next);
					}
					else
					{
						p.time++;
						q.push(p);
					}
				}
				else if (map[next.x][next.y] == '.'|| map[next.x][next.y] == 'T')
				{
					next.time = p.time + 1;
					v[next.x][next.y] = 1;
					q.push(next);
				}
			}
			
		}
	}

}
int main()
{
	while (cin >> n >> m)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 'S')
				{
					s.x = i;		//起始点初始化
					s.y = j;
					s.time = 0;
				}
			}
		memset(v, 0, sizeof(v));
		bfs();
	}
	return 0;
}