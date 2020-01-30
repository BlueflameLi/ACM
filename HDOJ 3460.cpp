#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, ans, maxl;
string str[10005];
int solve(string a, string b)
{
    int i;
    int l1 = a.length();
    int l2 = b.length();
    for (i = 0; i < l1 && i < l2; i++)
        if (a[i] != b[i])               //i为公共部分长度
            break;                      //打印第二个字符串，先删去第一个字符串的非公共部分l1-i
    return l1 + l2 - 2 * i;             //再输入第二个字符串非公共部分l2-i
}
int main()
{
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
            cin >> str[i];
        sort(str, str + n);             //先将字符串从小到大排序
        ans = str[0].length() + 1;      //打印第一个字符串
        maxl = str[0].length();         //找最长的字符串
        for (int i = 1; i < n; i++)
        {
            ans += solve(str[i - 1], str[i]) + 1;   //最后还有一个打印键要按
            maxl = maxl > str[i].length() ? maxl : str[i].length();
        }
        cout << ans + str[n - 1].length() - maxl << endl; //最后的字符串不需要删所以留下最长的那条
    }                                                     //先把最后n-1那条删了然后再减去最长的那条就行了
    return 0;
}