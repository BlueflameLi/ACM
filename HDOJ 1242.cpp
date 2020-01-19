#include <iostream>  
#include <queue>  
#include<cstring>
using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
char map[205][205];
int v[205][205];
int n, m;
struct node
{
    int x, y, step;
    friend bool operator < (node a, node b) //优先队列默认是大根堆
    {                                       //若a.step>b.step为真
        return a.step > b.step;             //则a<b,b排在a的前面
    }                                       //这样step小的就排在前面了
}s;                                         
bool check(node p)
{
    if (p.x < 0 || p.y < 0)
        return false;
    if (p.x >= n || p.y >= m)
        return false;
    if (map[p.x][p.y] == '#')
        return false;
    if (v[p.x][p.y])
        return false;
    return true;
}
void bfs()
{
    memset(v, 0,sizeof(v));
    priority_queue<node> q;     //建立优先队列  
    node p, next;
    v[s.x][s.y] = 1;
    q.push(s);
    while (!q.empty())
    {
        p = q.top();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            next.x = p.x + dx[i];
            next.y = p.y + dy[i];
            if (check(next))
            {
                if (map[next.x][next.y] == 'x')
                    next.step = p.step + 2; //遇到X时间加2  
                else
                    next.step = p.step + 1;   //否则正常加1 
                if (map[next.x][next.y] == 'r')  //因为有多个朋友，不好处理
                {                                //所以逆向，天使找到一个朋友就算得救了
                    cout << next.step << endl;
                    return;
                }
                v[next.x][next.y] = 1;
                q.push(next);
            }
        }
    }
    cout << "Poor ANGEL has to stay in the prison all his life." << endl;
}
int main()
{
    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == 'a')
                {
                    s.x = i;
                    s.y = j;
                    s.step = 0;
                }
            }
        bfs();
    }

    return 0;
}