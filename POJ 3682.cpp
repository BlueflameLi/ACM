#include <iostream>
#include <cstdio>
#define maxn 1005
using namespace std;

double E[maxn];
double F[maxn];
int k;
double p;
int main()
{
    while (cin >> k && k)
    {
        cin >> p;
        E[0] = 0;
        F[0] = 0;
        for (int i = 1; i <= k; i++)
        {
            E[i] = i / p;   //E(i)=p*E(i-1)+(1-p)*E(i)+1
            F[i] = F[i - 1] + 2 * E[i - 1] + 2 * (1 - p) / p * E[i] + 1 / p;
        }   //F(i)=p*(F(i-1)+2*E(i-1)+1)+(1-p)*(F(i)+2*E(i)+1)
        printf("%.3f %.3f\n", E[k], F[k]);//g++用%lf会WA，C++用%lfAC
    }
}