#include <iostream>
#include <cstring>

using namespace std;
struct Trie
{
    Trie *next[10];
    int v;
} * root;
int tot;
void creatTrie(string str) //建树
{
    Trie *p = root, *q;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - '0';
        if (p->next[id] == NULL)
        {
            q = new Trie; //创建一个新节点
            memset(q->next, 0, sizeof(q->next));
            q->v = 1;
            p->next[id] = q;
        }
        p = p->next[id];
    }
    p->v = -1; //标记结束点
}
bool findTrie(string str) //找前缀
{
    Trie *p = root;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - '0';
        if (i < l - 1 && p->next[id]->v == -1)
            return true;
        p = p->next[id];
    }
    return 0;
}
void del(Trie *p)
{
    for (int i = 0; i < 10; i++)
        if (p->next[i] != NULL)
            del(p->next[i]);
    delete p;
}
string s[10005];
int main()
{
    int t, n;
    cin >> t;
    while (t--)
    {
        root = new Trie; //创建根节点
        memset(root->next, 0, sizeof(root->next));
        root->v = 1;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            creatTrie(s[i]);
        }
        bool f = 0;
        for (int i = 0; i < n; i++)
            if (findTrie(s[i]))
            {
                cout << "NO" << endl;
                f = 1;
                break;
            }
        if (!f)
            cout << "YES" << endl;
        del(root);          //必须释放内存，否则MLE
    }
    return 0;
}