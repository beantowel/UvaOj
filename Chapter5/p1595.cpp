#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
typedef map<int, vector<int> > YtoZ;
float Mean10(const YtoZ::iterator &iter) {
    long sum = 0;
    for(int i = 0; i < iter->second.size(); i++)
        sum += iter->second[i];
    return sum/(float)iter->second.size();
}
int main() {
    int kase;
    cin >> kase;
    while(kase--) {
        int n, x, y;
        YtoZ m;
        cin >> n;
        while(n--) {
            cin >> x >> y;
            m[y].push_back(x);
        }
        map<int, vector<int> >::iterator iter;
        float mean = Mean10(m.begin());
        //cout << mean << " ";
        bool b = false;
        for(iter = m.begin(); iter != m.end(); iter++) {
            //cout << Mean10(iter) << " ";
            if(abs(Mean10(iter) - mean)>0.1) {
                cout << "NO" << endl;
                b = true;
                break;
            }
        }
        if(b) continue;
        cout << "YES" << endl;
    }
    return 0;
}