#include <iostream>
#include <cstring>

using namespace std;
struct Trie
{
    Trie *next[2];
    int v;
} * root;
int tot;
void creatTrie(string str)      //建树
{
    Trie *p = root, *q;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        int id = str[i] - '0';
        if (p->next[id] == NULL)
        {
            q = new Trie;      //创建一个新节点
            q->next[0] = q->next[1] = NULL;
            q->v = 1;
            p->next[id] = q;
        }
        p = p->next[id]; 
    }
    p->v = -1;                  //标记结束点
}
bool findTrie(string str)       //找前缀
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
int main()
{
    string s[10];
    while (cin >> s[0])
    {
        root = new Trie;        //创建根节点
        root->next[0] = root->next[1] = NULL;
        root->v = 1;
        creatTrie(s[0]);
        int k = 1;
        while (cin >> s[k] && s[k][0] != '9')
            creatTrie(s[k++]);
        bool f = 0;
        for (int i = 0; i < k; i++)
            if (findTrie(s[i]))
            {
                cout << "Set " << ++tot << " is not immediately decodable" << endl;
                f = 1;
                break;
            }
        if (!f)
            cout << "Set " << ++tot << " is immediately decodable" << endl;
    }
    return 0;
}