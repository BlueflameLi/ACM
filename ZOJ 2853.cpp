#include <iostream>
#include <cstring>
using namespace std;
struct Matrix
{
    double M[205][205];                 //本地上跑会栈溢出。。。但提交上去能AC，问题不大
};
Matrix mul(Matrix m1, Matrix m2, int n)
{
    Matrix m3;
    memset(m3.M, 0, sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                m3.M[i][j] += (m1.M[i][k] * m2.M[k][j]);
    return m3;
}

Matrix pow(Matrix m, int k, int n)
{
    Matrix ans;
    memset(ans.M, 0, sizeof(ans.M));
    for (int i = 0; i < n; i++)
        ans.M[i][i] = 1;
    while (k)
    {
        if (k & 1)
            ans = mul(ans, m, n);
        m = mul(m, m, n);
        k >>= 1;
    }
    return ans;
}
int main()
{
    int n, m, t;
    Matrix a;
    Matrix ans;
    while (cin >> n >> m && n && m)
    {
        memset(a.M, 0, sizeof(a.M));
        memset(ans.M, 0, sizeof(ans.M));
        for (int i = 0; i < n; i++)
            a.M[i][i] = 1;
        for (int i = 0; i < n; i++)
            cin >> ans.M[0][i];
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            int u, v;
            double p;
            cin >> u >> v >> p;
            a.M[u][v] += p;             //还是构造个矩阵，怎么构造，自己手工画几下就知道了
            a.M[u][u] -= p;
        }
        printf("%.0lf\n",mul(ans, pow(a, m, n), n).M[0][n - 1]);    //保留整数，四舍五入那种
    }
    return 0;
}
