#include <iostream>
#include <cstring>
#include <string>
using namespace std;
struct Trie
{
    int next[30];           //用指针会MLE
    int v;
} tri[500005];              //一开始开1e6MLE了。。。
int tot = 1;
void creatTrie(string str)
{
    int p = 0, q;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - 'a';
        if (tri[p].next[id] == 0)
        {
           tri[p].next[id] = tot;
           tot++;
        }
        p = tri[p].next[id];
        tri[p].v++;
    }
}
int findTrie(string str)
{
    int p = 0;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - 'a';
        if (tri[p].next[id] == 0)
            return 0;
        p = tri[p].next[id];
    }
    return tri[p].v;
}
int main()
{
    string s;
    memset(tri, 0, sizeof(tri));
    while (getline(cin, s))
    {
        if (s.length() == 0)        //读到空行跳出
            break;
        creatTrie(s);
    }
    while (getline(cin, s))
        cout << findTrie(s) << endl;
    return 0;
}