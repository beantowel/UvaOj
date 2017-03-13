#include <stdio.h>
#include <string.h>
const int maxIndex = 100000, maxFibolen = 3000, \
                     maxKase = 50000, maxDigit = 10, \
                               BASE = 1000000000, BASEW = 9;
int bigint[3][maxFibolen];
int ia = 0, ib = 1, ic = 2;
int lena, lenb, lenc;
int ans[maxKase];
struct Str40 {
    static const int MAXL = maxDigit;
    static const int WIDTH = BASEW;
    int x[MAXL];
    int len;
    Str40() {
        memset(x, 0, sizeof(x));
        len = 0;
    }
    Str40(const char *c) {
        memset(x, 0, sizeof(x));
        for(len = 0; (c[len] != '\0') && len < MAXL; len++)
            x[len] = c[len] - '0';
    }
    Str40(int *c, int n) {
        int k, i, j, t[WIDTH], ci;
        memset(t, 0, sizeof(t));
        for(i = n - 1, k = 0; i >= 0 && k < MAXL; i--) {
            ci = c[i];
            for(j = 0; j < WIDTH; j++) {
                if(!ci) break;
                t[j] = ci % 10;
                ci = ci / 10;
            }
            if(i != n - 1) j = WIDTH;
            for(j--; j >= 0 && k < MAXL; j--)
                x[k++] = t[j];
        }
        len = k;
    }
    bool isSub(const Str40 &b) const {
        if(len>b.len) return false;
        for(int i = 0; i < len; i++)
            if(b.x[i] != x[i]) return false;
        return true;
    }
};
Str40 cases[maxKase], fibo[maxIndex];
int main() {
    int kase;
    scanf("%d\n", &kase);
    char chr[40];
    for(int i = 0; i < kase; i++) {
        scanf("%s\n", chr);
        cases[i] = Str40(chr);
        ans[i] = -1;
    }
    memset(bigint, 0, sizeof(bigint));
    lena = 1;
    lenb = 1;
    bigint[ia][0] = 1;
    bigint[ib][0] = 1;
    fibo[0] = Str40(bigint[ia], lena);
    fibo[1] = Str40(bigint[ib], lenb);
    bool changA = true;
    int x, g;
    for(int i = 2; i < maxIndex; i++) {
        for(g = 0, lenc = 0;; lenc++) {
            if(g == 0 && lenc >= lena && lenc >= lenb) break;
            x = g;
            if(lenc < lena) x += bigint[ia][lenc];
            if(lenc < lenb) x += bigint[ib][lenc];
            bigint[ic][lenc] = x % BASE;
            g = x / BASE;
        }
        fibo[i] = Str40(bigint[ic], lenc);
        int t = lenc;
        lenc = lena;
        lena = lenb;
        lenb = t;
        ia = (ia + 1) % 3;
        ib = (ib + 1) % 3;
        ic = (ic + 1) % 3;
        // if(i == 11 || i == 1) {
        //     for(int j = 0; j < lenb; j++) {
        //         printf("%d ", bigint[ib][j]);
        //     }
        //     printf("\n");
        // }
    }
    //printf("done\n");
    for(int i = 0; i < kase; i++) {
        int j;
        for(j = 0; j < maxIndex; j++)
            if(cases[i].isSub(fibo[j])) {
                printf("Case #%d: %d\n", i + 1, j);
                break;
            }
        if(j == maxIndex) printf("Case #%d: -1\n", i + 1);
    }
    return 0;
}