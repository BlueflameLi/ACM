#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
 
using namespace std;
 
string s;			//存字符
bool a[30][30];		//a[i][j]表示i到j有路
bool v[30];			//标记是否访问过
bool flag;			//标记是否到终点
 
void dfs(int p)
{
	if (p == 'm' - 'a')
    {
		flag = 1;	//到终点了
		return;
    }
	for (int i = 0; i < 26; i++)
    {
		if (!v[i] && a[p][i])	//没访问过且刚好有路
        {
			v[i] = 1;
			dfs(i);				//访问一下
			if (flag)
				return;
        }
    }
}
 
int main()
{
    while(cin>>s)
    {
        memset(a,0,sizeof(a));
        memset(v,0,sizeof(v));
        a[s[0]-'a'][s[s.length()-1]-'a']=1;			//我们只管开头和结尾
        while(cin>>s&&s[0]!='0')
            a[s[0]-'a'][s[s.length()-1]-'a']=1;
		flag=0;
        v[1]=1;										//起点别忘标记
        dfs(1);
		if (flag)
			cout << "Yes." << endl;
        else
			cout << "No." << endl;
    }
    return 0;
}
