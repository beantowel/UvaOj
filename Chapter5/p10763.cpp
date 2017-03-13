#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct Stu {
    int x, y;
    Stu(int a, int b): x(a), y(b) {}
    bool operator <(const Stu &b) const {
        if(x < b.y) return true;
        else return false;
    }
    bool operator ==(const Stu &b)const {
        return !(*this < b) && !(b < *this);
    }
};
int main() {
    int n;
    vector<Stu> xy, yx;
    while(cin >> n && n != 0) {
        xy.clear();
        yx.clear();
        for(int i = 0; i < n; i++) {
            int t1, t2;
            cin >> t1 >> t2;
            xy.push_back(Stu(t1, t2));
            yx.push_back(Stu(t2, t1));
        }
        sort(xy.begin(), xy.begin() + n);
        sort(yx.begin(), yx.begin() + n);
        int i;
        for(i = 0; i < n; i++)
            if(!(xy[i] == yx[i])) {
                cout << "NO" << endl;
                break;
            }
        if(i == n) cout << "YES" << endl;
    }
    return 0;
}