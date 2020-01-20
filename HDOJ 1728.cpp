#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int n, m, t, k;
int a1, b1, a2, b2;        //因为y1之类的变量名有时候会函数冲突，所以我干脆改成了a1,b1这种
int dx[4] = {1, 0, -1, 0}; //方向
int dy[4] = {0, 1, 0, -1};
char map[105][105];
int v[105][105]; //标记一下，避免重复
struct node
{
    int x, y;
    int turn;      //记录转弯次数
} s;               //s是起始点
bool check(node p) //判断是否越界，是否有障碍
{
    if (p.x <= 0 || p.y <= 0)
        return false;
    if (p.x > n || p.y > m)
        return false;
    if (map[p.x][p.y] == '.')
        return true;
    if (p.x == b2 && p.y == a2)//别忘了x和y是反的
        return true;
    return false;
}
void bfs()
{
    queue<node> q;
    node p, e;
    memset(v, 0, sizeof(v)); //清空
    s.turn = -1;             //起点往任意方向都没有转弯
    q.push(s);               //起点入队，初始化要在入队前做
    v[s.x][s.y] = 1;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        //cout << p.x << ' ' << p.y << ' ' << p.turn << endl;
        if (p.turn >= k)
            continue; //转弯次数超了的，直接过
        for (int i = 0; i < 4; i++)
        {
            e.x = p.x + dx[i];
            e.y = p.y + dy[i];
            e.turn = p.turn + 1;
            //cout << p.x << ' ' << p.y << ' ' << e.x << ' ' << e.y << endl;
            while (check(e)) //因为尽量少拐弯，所以一直往一个方向冲就行了
            {

                if (e.x == b2 && e.y == a2)
                {
                    cout << "yes" << endl;
                    return;
                }
                if (!v[e.x][e.y])
                {
                    v[e.x][e.y] = 1;
                    q.push(e);
                }
                e.x += dx[i];
                e.y += dy[i]; //继续再这个方向上冲
            }
        }
    }
    cout << "no" << endl;
}
int main()
{

    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> map[i][j];
        cin >> k >> a1 >> b1 >> a2 >> b2;      //注意k是第一个！！！
        s.x = b1;   //注意x和y是反的！！！
        s.y = a1;
        bfs();
    }
    return 0;
}