#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define maxn 1005
using namespace std;
const int m1 = 23, m2 = 28, m3 = 33;
const int M = m1 * m2 * m3;
const int M1 = m2 * m3, M2 = m1 * m3, M3 = m1 * m2;
int M1_, M2_, M3_;//Mi_为Mi的逆元乘上Mi
int p, e, i, d;
int ans;
int cnt;
int t;
int main()
{
	for (int j = 1;; j++)		//j就是Mi的逆元，其实手算也行，很小的，只不过我比较懒
		if (j * M1 % m1 == 1)
		{
			M1_ = j * M1;
			break;
		}
	for (int j = 1;; j++)
		if (j * M2 % m2 == 1)
		{
			M2_ = j * M2;
			break;
		}
	for (int j = 3;; j++)
		if (j * M3 % m3 == 1)
		{
			M3_ = j * M3;
			break;
		}
	cin >> t;
	while (t--)
	{
		cnt = 0;
		while (cin >> p >> e >> i >> d)
		{
			if (p == -1 && e == -1 && i == -1 && d == -1)
				break;
			ans = (p * M1_ + e * M2_ + i * M3_) % M - d;
			if (ans <= 0)
				ans += M;
			cout << "Case " << ++cnt << ": the next triple peak occurs in " << ans << " days." << endl;
		}
	}
	return 0;
}