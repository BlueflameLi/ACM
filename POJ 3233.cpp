#include <iostream>
#include <cstring>
using namespace std;
int mod;
struct Matrix
{
    int M[70][70];          //矩阵扩充了4倍，所以这里要至少开60*60
};
Matrix mul(Matrix m1, Matrix m2, int n)
{
    Matrix m3;
    memset(m3.M, 0, sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)     //一定要加的时候就取模，否则会溢出
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
    memset(m.M, 0, sizeof(m.M));
    cin >> n >> k >> mod;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> m.M[i][j];
            if (i == j)             //构造一个特殊的矩阵
            {
                m.M[i][j + n] = 1;
                m.M[i + n][j + n] = 1;
            }
        }
    m = pow(m, k + 1, 2 * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                m.M[i][j + n]--;
                if (m.M[i][j + n] < 0)      //因为是先取模的，所以可能会有负的，要加回去
                    m.M[i][j + n] += mod;
            }
            cout << m.M[i][j + n] << ' ';
        }
        cout << endl;
    }
    return 0;
}