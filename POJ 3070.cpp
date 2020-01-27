#include <iostream>
#include <cstring>

using namespace std;
struct Matrix
{
    int M[5][5];
};
Matrix mul(Matrix m1, Matrix m2, int n)
{
    Matrix m3;
    memset(m3.M,0,sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                m3.M[i][j] = (m3.M[i][j] + (m1.M[i][k] % 10000) * (m2.M[k][j] % 10000)) % 10000;
    return m3;
}
Matrix pow(Matrix m, int n)     //矩阵快速幂
{
    Matrix ans;
    ans.M[0][0] = 1;            //单位矩阵，相当于数字1
    ans.M[1][1] = 1;
    ans.M[1][0] = 0;
    ans.M[0][1] = 0;
    while (n)
    {
        if (n & 1)              //就是把普通的快速幂中的普通乘法换成矩阵的乘法
            ans = mul(ans, m, 2);
        m = mul(m, m, 2);
        n >>= 1;
    }
    return ans;
}
int main()
{
    int n;
    Matrix m;
    m.M[0][0] = 1;
    m.M[1][0] = 1;
    m.M[0][1] = 1;
    m.M[1][1] = 0;
    while (cin >> n && n != -1)
        cout << pow(m, n).M[1][0] % 10000 << endl;
    return 0;
}