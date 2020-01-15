#include<iostream>
#include<queue>
using namespace std;
int t;
int n, m;
int r = 6;
int dx[4] = { 0,1,-1,0 };			//dx和dy两个数组控制方向
int dy[4] = { 1,0,0,-1 };
int map[10][10];					//将迷宫的地图存下来
struct node
{
	int x, y;						//x和y是坐标
	int time;						//剩余时间
	int step;						//步数
}s;									//s是起始点

void bfs()
{
	queue<node> q;
	q.push(s);						//将起始点入队
	node next, p;
	while (!q.empty())
	{
		p = q.front();				//队首是p
		q.pop();					//出队
		if (p.time == 1)			//如果时间只剩1分钟了还没到终点或者重置点，那么就挂了
			continue;
		for (int i = 0; i < 4; i++)
		{
			next.x = p.x + dx[i];	//计算下一个点next的坐标
			next.y = p.y + dy[i];
			//cout << next.x <<' '<< next.y<<endl;
			if (next.x >= 0 && next.x < n && next.y>=0 && next.y < m && map[next.x][next.y])
			{											//如果没有越界且不是墙就走
				next.time = p.time - 1;					//时间减少一分钟
				next.step = p.step + 1;					//步数加1
				if (map[next.x][next.y] == 4)			//到达重置点
				{
					next.time = 6;						//时间重置
					map[next.x][next.y] = 0;			//既然每次到达重置点时间都剩下6分钟，
				}										//那么显然后面再来重置点没有意义，肯定不是最短路线
				q.push(next);							//下一个点进队
			}
			if (map[next.x][next.y] == 3)				//到终点了，输出步数，退出
			{
				cout << next.step << endl;
				return;
			}
		}
	}
	cout << -1 << endl;			//队列都空了还没找到终点，挂了

}
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 2)
				{
					s.x = i;		//起始点初始化
					s.y = j;
					s.time = 6;
					s.step = 0;
				}
			}
		bfs();
	}
	return 0;
}