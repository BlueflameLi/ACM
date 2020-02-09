#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <map>

using namespace std;

int n;
int m[505][505], g[505][505];      //m[i][j]表示编号为i的女生对编号为j的男生的喜欢排名
//g[i][j]表示编号为i的男生，第j喜欢的女生的编号，两个数组意义不同，千万别搞错
int m_g[505], g_m[505];            //m_g[i]为编号为i的女生的对象的编号，g_m[i]为编号i的男生的对象的编号
int p[505];                        //p[i]为编号为i的男生表白次数
map<string, int> mp_m, mp_g;        //将名字转换成数字编号
string sm[505], sg[505];            //数字编号对应的名字，sm是女生名字，sg是男生名字
int main()
{
    while (cin >> n)
    {
        mp_m.clear();               //多组，需清空
        mp_g.clear();
        for (int i = 1; i <= n; i++)
        {
            string s1, s2;
            cin >> s1;
            mp_g[s1] = i;           //男生编号
            sg[i] = s1;             //记录编号对应的男生名字
            for (int j = 1; j <= n; j++)
            {
                cin >> s2;
                if (!mp_m[s2])
                {
                    mp_m[s2] = j;   //女生编号
                    sm[j] = s2;     //记录编号对应的女生名字
                }
                g[i][j] = mp_m[s2];  //记录i男生第j喜欢的女生的编号
            }
        }
        for (int i = 1; i <= n; i++)
        {
            string s1, s2;
            cin >> s1;
            for (int j = 1; j <= n; j++)
            {
                cin >> s2;
                m[mp_m[s1]][mp_g[s2]] = j;  //记录女生s1对男生s2的喜欢排名
            }
        }
        bool flag = 0;
        memset(m_g, 0, sizeof(m_g));        //别忘清空
        memset(g_m, 0, sizeof(g_m));
        memset(p, 0, sizeof(p));
        while (!flag)
        {
            flag = 1;
            for (int i = 1; i <= n; i++)
            {
                if (!g_m[i] && p[i] < n)    //如果i号男生没有对象，且还有没表白过的女生
                {
                    int mm = g[i][++p[i]];  //要表白的女生
                    if (!m_g[mm])           //如果这个女生没对象
                    {
                        m_g[mm] = i;        //配对成功
                        g_m[i] = mm;
                    }
                    else if (m[mm][i] < m[mm][m_g[mm]]) //如果这个女生更喜欢你
                    {
                        g_m[m_g[mm]] = 0;       //把原来的男生甩了
                        m_g[mm] = i;            //匹配成功
                        g_m[i] = mm;
                    }
                    flag = 0;
                }
            }
        }
        /* flag = 0;                        //这边是判断匹配失败的情况，不过貌似没有这个数据点
        for (int i = 1; i <= n; i++)        //所以可以不写
            if (!g_m[i])
            {
                flag = 1;
                break;
            }
        if (flag)
            cout << "Impossible" << endl;
        else*/
        for (int i = 1; i <= n; i++)
            cout << sg[i] << ' ' << sm[g_m[i]] << endl;
    }
    return 0;
}
