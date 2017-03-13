#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;
map<long long, int> sums;
int cnt;
string line;
void dfs(int depth, int &cur) {
    if(line[cur] == '[') {
        cur++;
        dfs(depth + 1, cur);
        while(line[cur] != ',') cur++;
        cur++;
        dfs(depth + 1, cur);
        while(line[cur] != ']') cur ++;
    } else {
        long long d = 0, sum;
        while(isdigit(line[cur]))
            d = d * 10 + line[cur++] - '0';
        cur--;
        sum = d << depth;
        sums[sum]++;
        cnt++;
    }
}
int main() {
    int k, cur;
    cin >> k;
    while(k--) {
        cur = 0;
        cnt = 0;
        sums.clear();
        cin >> line;
        dfs(0, cur);
        int max = 0;
        map<long long, int>::iterator iter;
        for(iter = sums.begin(); iter != sums.end(); iter++)
            max = iter->second > max ? iter->second : max;
        cout << cnt - max << endl;
    }
    return 0;
}