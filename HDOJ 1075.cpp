#include <iOStream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
using namespace std;
char s[12], s1[12], s2[12], c;
int tot;
map<string, string> ma;
int main()
{
    cin >> s;
    while (cin >> s1 >> s2&&strcmp(s1, "END"))  //第二个START会和第一个END一起读掉
        ma[s2] = s1;
    getchar();
    while (scanf("%c", &c))
    {
        if (c>='a'&&c<='z'||c>='A'&&c<='Z') //大写字母是因为要读END
            s[tot++] = c;
        else
        {
            s[tot] = '\0';
            tot = 0;
            if (!strcmp(s, "END"))
                    break;
            if (ma.count(s))
                cout << ma[s];
            else
                cout << s;
            cout << c;
        }
    }
    return 0;
}
