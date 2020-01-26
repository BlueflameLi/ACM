#include <iostream>
#include <cstring>

using namespace std;
struct Matrix           //用一个结构体来表示矩阵
{
    int M[15][15];
};
Matrix mul(Matrix m1, Matrix m2, int n) //矩阵乘法
{
    Matrix m3;
    memset(m3.M, 0, sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                m3.M[i][j] = (m3.M[i][j] + (m1.M[i][k] % 9973) * (m2.M[k][j] % 9973)) % 9973;
    return m3;
}
int Tr(Matrix m, int n)        //对角和
{
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = (ans + m.M[i][i]) % 9973;
    return ans;
}
Matrix pow(Matrix m, int k, int n)      //就是普通的快速幂，把数的乘换成矩阵的乘
{
    Matrix ans;
    memset(ans.M, 0, sizeof(ans.M));
    for (int i = 0; i < n; i++)         //这是一个单位矩阵，相当于数字1，任何矩阵乘一个单位矩阵等于本身
        ans.M[i][i] = 1;
    while (k)
    {
        if (k & 1)                      //快速幂应该都会了吧
            ans = mul(ans, m, n);
        m = mul(m, m, n);
        k >>= 1;
    }
    return ans;
}
int main()
{
    int t;
    int n, k;
    Matrix m;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> m.M[i][j];
        cout << Tr(pow(m, k, n), n) << endl;
    }

    return 0;
}