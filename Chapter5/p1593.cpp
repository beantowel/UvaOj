#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
string sin;
vector<string> s[1000];
int maxlen[1000];
int nline;
int main() {
    memset(maxlen, 0, sizeof(maxlen));
    for(nline = 0; getline(cin, sin); nline++) {
        string temp;
        stringstream ss(sin);
        for(int j = 0; ss >> temp; j++) {
            s[nline].push_back(temp);
            maxlen[j] = max(maxlen[j], (int)temp.size());
        }
    }
    cout.flags(ios::left);
    for(int i = 0; i < nline; i++) {
        int j;
        for(j = 0; j < s[i].size()-1; j++) {
            cout << setw(maxlen[j] + 1) << s[i][j];
        }
        cout << s[i][j] << endl;
    }
    return 0;
}