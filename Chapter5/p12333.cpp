#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
const int maxIndex = 100000, maxFibolen = 3000, \
                     maxKase = 50000, maxDigit = 40, \
                               BASE = 1000000000, BASEW = 9;
int bigint[3][maxFibolen];
int abc[3] = {0, 1, 2};
int lenabc[3] = {1, 1, 0};
struct Str40 {
    static const int MAXL = maxDigit;
    static const int WIDTH = BASEW;
    int x[MAXL];
    Str40() {
        memset(x, -1, sizeof(x));
    }
    Str40(const char *c) {
        memset(x, -1, sizeof(x));
        int len;
        for(len = 0; (c[len] != '\0') && len < MAXL; len++)
            x[len] = c[len] - '0';
    }
    Str40(int *c, int n, int maxl) {
        int k, i, j, t[WIDTH], ci;
        memset(x,-1,sizeof(x));
        for(i = n - 1, k = 0; i >= 0 && k < maxl; i--) {
            memset(t, 0, sizeof(t));
            ci = c[i];
            for(j = 0; j < WIDTH; j++) {
                if(!ci) break;
                t[j] = ci % 10;
                ci = ci / 10;
            }
            if(i != n - 1) j = WIDTH;
            for(j--; j >= 0 && k < maxl; j--)
                x[k++] = t[j];
        }
    }
    bool operator <(const Str40 &b) const {
        for(int i = 0; i < MAXL; i++) {
            if(x[i] > b.x[i]) return false;
            else if(x[i] < b.x[i]) return true;
        }
        return false;
    }
    void printStr40(){        
        // for(int i=0;i<MAXL;i++)
        //     printf("%2d",x[i]);
        // printf("\n");
    }
};
Str40 cases[maxKase], temp;
map<Str40, int> fibo;
int main() {
    int kase;
    scanf("%d\n", &kase);
    char chr[40];
    for(int i = 0; i < kase; i++) {
        scanf("%s\n", chr);
        cases[i] = Str40(chr);
    }
    memset(bigint, 0, sizeof(bigint));
    lenabc[abc[0]] = 1;
    lenabc[abc[1]] = 1;
    bigint[abc[0]][0] = 1;
    bigint[abc[1]][0] = 1;
    fibo.insert(make_pair(Str40(bigint[abc[0]], lenabc[abc[0]], BASEW), 0));
    bool changA = true;
    int x, g;
    for(int i = 2; i < maxIndex; i++) {
        for(g = 0, lenabc[abc[2]] = 0;; lenabc[abc[2]]++) {
            if(g == 0 && lenabc[abc[2]] >= lenabc[abc[0]] && lenabc[abc[2]] >= lenabc[abc[1]]) break;
            x = g;
            if(lenabc[abc[2]] < lenabc[abc[0]]) x += bigint[abc[0]][lenabc[abc[2]]];
            if(lenabc[abc[2]] < lenabc[abc[1]]) x += bigint[abc[1]][lenabc[abc[2]]];
            bigint[abc[2]][lenabc[abc[2]]] = x % BASE;
            g = x / BASE;
        }

        for(int j = maxDigit; j > 0; j--) {
            temp = Str40(bigint[abc[2]], lenabc[abc[2]], j);
            if(fibo.find(temp) != fibo.end()) continue;
            fibo.insert(make_pair(temp, i));
        }
        // if(i==88 || i==89 ){
        //     for(int j=0;j<lenabc[abc[2]];j++){
        //         printf("%d ",bigint[abc[2]][j]);
        //     }
        //     printf("\n");
        //     temp=Str40(bigint[abc[2]], lenabc[abc[2]], maxDigit);
        //     temp.printStr40();
        // }

        abc[0] = (abc[0] + 1) % 3;
        abc[1] = (abc[1] + 1) % 3;
        abc[2] = (abc[2] + 1) % 3;
    }
    map<Str40, int>::iterator iter;
    for(int i = 0; i < kase; i++) {
        iter = fibo.find(cases[i]);
        if(iter != fibo.end()) printf("Case #%d: %d\n", i + 1, iter->second);
        else printf("Case #%d: -1\n", i + 1);
    }
    return 0;
}