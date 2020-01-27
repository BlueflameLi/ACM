#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int t;
int x[5], y[5];
struct Matrix
{
    int M[30][30];
};
Matrix mul(Matrix m1, Matrix m2, int n)
{
    Matrix m3;
    memset(m3.M, 0, sizeof(m3.M));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
                m3.M[i][j] += (m1.M[i][k] * m2.M[k][j]);
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
void print(Matrix res, int nm)
{
    if (!res.M[0][nm - 1])              //没有长度为p的到终点的路径输出false
    {
        printf("False\n");
        return;
    }
    for (int i = 1; i < nm - 1; i++)
        if (res.M[0][i])               //除到终点外还有到其他场景的长度为p的路径输出maybe
        {
            printf("Maybe\n");
            return;
        }
    printf("True\n");                  //只有一条长度为p的路径且到终点，输出true
}
int main()
{
    int n, m;
    Matrix ans;
    cin >> t;
    while (t--)
    {
        scanf("%d%d", &n, &m);
        getchar();
        memset(ans.M, 0, sizeof(ans.M));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                scanf("((%d,%d),(%d,%d),(%d,%d),(%d,%d))", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
                getchar();
                if (i == n - 1 && j == m - 1)   //到了终点就会立马离开，所以终点不需要出口
                    continue;
                int u = i * m + j;
                for (int k = 0; k < 4; k++)
                {
                    int v = m * (x[k] - 1) + y[k] - 1;
                    ans.M[u][v] = 1;            //建立邻接矩阵
                }
            }
        int q;
        scanf("%d", &q);
        while (q--)
        {
            int p;
            int nm = n * m;
            scanf("%d", &p);
            Matrix res = pow(ans, p, nm);       //邻接矩阵的p次方就是长度为p的路径
            print(res, nm);
        }
        printf("\n");
    }
    return 0;
}