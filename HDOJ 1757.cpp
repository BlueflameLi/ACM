#include <iostream>
#include <cstring>
using namespace std;
int mod;
struct Matrix
{
    int M[15][15];
};
Matrix mul(Matrix m1, Matrix m2, int n)
{
    Matrix m3;
    memset(m3.M, 0, sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
                m3.M[i][j] += (m1.M[i][k] * m2.M[k][j]) % mod;
            m3.M[i][j] %= mod;
        }
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
    int n, k;
    Matrix m;
    Matrix ans;
    for (int i = 0; i < 10; i++)                    //这里是初始的F(0)~F(9)
        ans.M[i][0] = 9 - i;
    while (cin >> n >> mod)
    {
        memset(m.M, 0, sizeof(m.M));
        for (int i = 0; i < 10; i++)                //构造矩阵，用矩阵快速幂求递推式
        {
            cin >> m.M[0][i];
            m.M[i + 1][i] = 1;
        }

        if (n < 10)
            cout << ans.M[9 - n][0] % mod << endl; //这边也要记得mod
        else
            cout << mul(pow(m, n - 9, 10), ans, 10).M[0][0] << endl;
    }
    return 0;
}