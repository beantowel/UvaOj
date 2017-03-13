#include <iostream>
#include <queue>
using namespace std;
int n;
int main() {
    while(cin >> n && n != 0) {
        queue<int> q;
        for(int i = 0; i < n; i++)
            q.push(i + 1);
        cout << "Discarded cards:";
        int j = 0;
        while(q.size() > 1) {
            int t = q.front();
            q.pop();
            q.push(q.front());
            q.pop();
            if(j++) cout << ",";
            cout << " " << t;
        }
        cout << endl << "Remaining card: " \
        << q.front() << endl;
    }
}