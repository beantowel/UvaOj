#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
struct Seq;
struct Seq {
    vector<int> x;
    Seq(): x() {};
    Seq(int *begin, int *end) {
        int *i;
        for(i = begin; i != end; i++)
            x.push_back(*i);
    }
    bool operator < (const Seq &s) const {
        for(int i = 0; i < x.size(); i++)
            if(x[i] < s.x[i]) return true;
            else if(x[i] > s.x[i]) return false;
        return false;
    }
    const Seq Ducci() {
        Seq s;
        int i;
        for(i = 0; i < x.size() - 1; i++)
            s.x.push_back(abs(x[i] - x[i + 1]));
        s.x.push_back(abs(x[i] - x[0]));
        return s;
    }
    bool isZero() {
        for(int i = 0; i < x.size(); i++)
            if(x[i] != 0) return false;
        return true;
    }
    friend ostream &operator << (ostream &os, const Seq &s) {
        for(int i = 0; i < s.x.size(); i++) os << setw(3) << s.x[i];
        os << endl;
        return os;
    }
};
set<Seq> a;
int kase, n , temp[15];
Seq t;
int main() {
    cin >> kase;
    for(int i = 0; i < kase; i++) {
        cin >> n;
        for(int j = 0; j < n; j++)
            cin >> temp[j];
        a.clear();
        Seq seq1(temp, temp + n);
        a.insert(seq1);
        t = seq1;
        //cout << t;
        int j;
        for(j=0;j<1002;j++){
            if(t.isZero()){
                cout<<"ZERO"<<endl;
                break;
            }
            t=t.Ducci();
            //cout << t;
            if(a.find(t)!=a.end()){
                cout<<"LOOP"<<endl;
                break;
            }
            a.insert(t);
        }
    }
    return 0;
}