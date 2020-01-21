
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
map<string, map<string, double>> ma;    //map二维
string s[50];
int n, m, t = 1;
void floyd() //floyd算法，很好记，kij，核心代码就五行
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (ma[s[i]][s[j]] < ma[s[i]][s[k]] * ma[s[k]][s[j]])
                    ma[s[i]][s[j]] = ma[s[i]][s[k]] * ma[s[k]][s[j]];
    for (int i = 1; i <= n; i++) //进行判断
        if (ma[s[i]][s[i]] > 1.0) //如果符合这个关系，说明能成立
        {
            cout << "Case " << t++ << ": "      //这边格式是vs code自动的，看着挺整齐
                 << "Yes" << endl;
            return;
        }
    cout << "Case " << t++ << ": "
         << "No" << endl;
}
int main()
{
    while (cin >> n && n != 0)
    {
        ma.clear();                      //清空
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i]; //输入字符串
            ma[s[i]][s[i]] = 1.0;       //map是个好东西
        }
        cin >> m;
        double c;
        string a, b;
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> c >> b;
            ma[a][b] = c;
        }
        floyd();
    }
    return 0;
}
