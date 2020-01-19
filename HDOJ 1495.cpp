#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int v[105][105][105];       //标记每种状态是否出现过
int a[3];                   //a[0]是S，a[1]是N,a[2]是M
int half;                   //半瓶水的体积
struct node
{
    int V[3];               //跟a数组一样
    int step;
};
bool check(node p)          //判断是否平分了
{
    if (p.V[0] == half && p.V[1] == half)
        return true;
    if (p.V[0] == half && p.V[2] == half)
        return true;
    if (p.V[1] == half && p.V[2] == half)
        return true;
    return false;
}
void bfs()
{
    if (a[0] % 2)           //既然都是整数，显然倒不出0.5来
    {                       //所以奇数剪了
        cout << "NO" << endl;
        return;
    }
    memset(v, 0, sizeof(v));
    queue<node> q;
    node p, next;
    half = a[0] >> 1;
    p.V[0] = a[0];
    p.V[1] = 0;
    p.V[2] = 0;
    p.step=0;
    v[p.V[0]][p.V[1]][p.V[2]] = 1;
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        for (int i = 0; i < 3; i++)
        {
            if (p.V[i] > 0)    //倒之前总得有可乐
            {
                for (int j = 0; j < 3; j++)
                {
                    if (i == j || p.V[j] == a[j])
                        continue;       //显然不能倒给自己也不能给满的杯子倒
                    next = p;           //这个千万别忘了
                    if (next.V[i] > a[j] - next.V[j])//能倒满的情况
                    {
                        next.V[i] -= a[j] - next.V[j];
                        next.V[j] = a[j];
                    }
                    else                            //倒不满或刚好倒满的情况
                    {
                        next.V[j] += next.V[i];
                        next.V[i] = 0;
                    }

                    if (!v[next.V[0]][next.V[1]][next.V[2]])
                    {
                        next.step++;
                        if (check(next))
                        {
                            cout << next.step << endl;
                            return;
                        }
                        v[next.V[0]][next.V[1]][next.V[2]] = 1;
                        q.push(next);
                    }
                }
            }
        }
    }
    cout << "NO" << endl;
}
int main()
{
    while (cin >> a[0] >> a[1] >> a[2])
    {
        if (!(a[0] && a[1] && a[2]))
            break;
        bfs();
    }
    return 0;
}