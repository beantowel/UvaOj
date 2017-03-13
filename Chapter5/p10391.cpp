#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
vector<string> v;
set<string> s;
int main() {
    string t;
    while(cin >> t) {
        s.insert(t);
        v.push_back(t);
    }
    for(int i = 0; i < v.size(); i++) {
        int j = i;
        while(j--) {
            int found=v[i].find(v[j]);
            if(found!=0) continue;
            string sub2 = v[i].substr(v[j].size(), \
                                      v[i].size() - v[j].size());
            if(s.find(sub2) != s.end()) {
                cout << v[i] << endl;
                break;
            }
        }
    }
    return 0;
}