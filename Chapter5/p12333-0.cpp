#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct BigInteger {
    static const int BASE = 10;
    static const int WIDTH = 1;
    vector<short int> s;
    BigInteger(long long num = 0) {
        *this = num;
    }
    BigInteger operator =(long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num = num / BASE;
        } while(num > 0);
        return *this;
    }
    BigInteger operator +(const BigInteger &b) const {
        BigInteger c;
        c.s.clear();
        for(int i = 0, g = 0;; i++) {
            if(g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if(i < s.size()) x += s[i];
            if(i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    bool isStartWith(const string &str) const {
        if(s.size() < str.size()) return false;
        for(int i = 0; i < str.size(); i++)
            if((str[i] - '0') != s[s.size() - i - 1]) return false;
        return true;
    }
    friend ostream &operator <<(ostream &os, const BigInteger &a) {
        for(int i = a.s.size() - 1; i >= 0; i--) os << a.s[i];
        os << endl;
        return os;
    }
};
int main() {
    int kase, n;
    vector<string> strs;
    vector<int> index;
    cin >> kase;
    n = kase;
    while(kase--) {
        string s;
        cin >> s;
        strs.push_back(s);
        if(s != "1") index.push_back(-1);
        else index.push_back(0);
    }
    BigInteger a(1), b(1), c;
    bool changeA = true;
    for(int i = 2; i < 100000; i++) {
        c = a + b;
        //cout<<c;
        for(int j = 0; j < strs.size(); j++) {
            if(index[j] != -1) continue;
            if(c.isStartWith(strs[j])) {
                index[j] = i;
                n--;
                //cout <<"case" << j+1 << ":" << i << endl;
            }
        }
        if(changeA) a = c;
        else b = c;
        changeA = !changeA;
        if(n == 0) break;
    }
    for(int i = 0; i < strs.size(); i++) {
        cout << "Case #" << i + 1 << ": " << index[i] << endl;
    }
    return 0;
}