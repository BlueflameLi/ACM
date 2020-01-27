#include <iostream>
#include <cstring>
using namespace std;
int mod;
struct Matrix
{
    int M[5][5];
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
    ans.M[0][0] = 9;
    ans.M[1][0] = 6;
    ans.M[2][0] = 4;
    ans.M[3][0] = 2;
    while (cin >> n >> mod)
    {
        memset(m.M, 0, sizeof(m.M));
        m.M[0][0] = m.M[0][2] = m.M[0][3] = 1;              //利用矩阵快速幂来算递推式
        m.M[1][0] = m.M[2][1] = m.M[3][2] = 1;              //F(n)=F(n-1)+F(n-3)+F(n-4)
        if (n < 5)
            cout << ans.M[4 - n][0] % mod << endl;          //这边也要记得mod
        else
            cout << mul(pow(m, n - 4, 4), ans, 4).M[0][0] << endl;
    }
    return 0;
}