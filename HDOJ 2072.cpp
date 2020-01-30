#include <iostream>
#include <set>
#include <sstream>
using namespace std;
set<string> Set;
string s1, s2;
int main()
{
    while (getline(cin, s1))
    {
        if (s1 == "#")
            break;
        istringstream istr(s1);
        Set.clear();
        while (istr >> s2)
            Set.insert(s2);
        cout << Set.size() << endl;
    }
    return 0;
}