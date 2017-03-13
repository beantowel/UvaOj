#include <iostream>
#include <cstring>
//#include <queue>
#include <vector>
using namespace std;
int FindOrder(int pos, vector<int> &v) {
    for(int i = 0; i < v.size(); i++)
        if(v[i] >= pos) return i;
    if(v.size() > 0) return 0;
    return -1;
}
int main() {
    int kase;
    cin >> kase;
    while(kase--) {
        int n, mpos, level = -1, time = 0;
        vector<int> a[9];
        cin >> n >> mpos;
        for(int i = 0; i < n; i++) {
            int t;
            cin >> t;
            a[t - 1].push_back(i);
            if(i == mpos) level = t - 1;
        }
        int pos=a[level][0], i; //pos in vector
        for(i = 8; i > level; i--)
            if(a[i].size()) {
                time += a[i].size();
                pos = a[i][a[i].size()-1];
                // cout<<i<<" "<<pos<<endl;
                break;
            };
        for(i--; i > level; i--) {
            if(a[i].size() == 0) continue;
            int order = FindOrder(pos, a[i]);
            order = (order + a[i].size() - 1) % a[i].size();
            pos = a[i][order];
            time += a[i].size();
            // cout<<i<<" "<<pos<<endl;
        }
        i = FindOrder(pos, a[level]);
        // cout<<i<<" "<<a[level][i]<<endl;
        for(; a[level][i] != mpos; (i = (i + 1) % a[level].size()))
            time++;
        cout << time + 1 << endl;
    }
    return 0;
}