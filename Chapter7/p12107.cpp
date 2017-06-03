#include <cstdio>
#include <cstring>
const int maxL = 10, maxV = 10000;
const int start[] = {0, 1, 10, 100, 1000};
const int end[] = {0, 9, 99, 999, 9999};
int maxD, iChoose, tCnt;
int la, lb, lc;
char c[maxL], ans[maxL], t[maxV][maxL];
char dfsC[maxL];
int compare(char *t)
{
    int cnt = 0;
    for(int i = 0; c[i] != '\0'; i++)
        if(c[i] != '*' && c[i] != t[i]) cnt++;
    return cnt;
}
void update(char *t)
{
    bool smaller = false;
    for(int i = 0; c[i] != '\0'; i++) {
        if(t[i] < ans[i]) {
            smaller = true;
            break;
        }else if(t[i] > ans[i]) break;
    }
    if(!smaller) return;
    memcpy(ans, t, sizeof(ans));
}
bool search()
{
    la = 0;
    lb = 0;
    lc = 0;
    while(c[la] != ' ') la++;
    while(c[(la + 1) + lb] != ' ') lb++;
    while(c[(la + lb + 2) + lc] != '\0') lc++;

    bool valid = false; //big value
    tCnt = 0;
    for(int a = start[la]; a <= end[la]; a++)
        for(int b = start[lb]; b <= end[lb]; b++) {
            int cc = a * b;
            if(cc < start[lc]) continue;
            if(cc > end[lc]) break;
            sprintf(t[tCnt], "%d %d %d", a, b, cc);
            int diff = compare(t[tCnt]);
            if(diff == 0) {
                sprintf(t[tCnt], "%d %d %d", a, b, cc);
                tCnt++;
                valid = true;
            }
        }
    return valid;
}
bool dfs(int d, int i)
{
    if(d == maxD) {
        for(int j = 0; j < tCnt; j++)
            if(j != iChoose && compare(t[j]) == 0) return false;
        return true;
    }
    //.->[0-9]
    for(int j = i; j >= 0; j--) {
        if(dfsC[j] == ' ') continue;
        if(dfsC[j] != t[iChoose][j]) {
            c[j] = t[iChoose][j];
            if(dfs(d + 1, j - 1)) return true;
            c[j] = dfsC[j];
        }
    }
    return false;
}
void specialize()
{
    memcpy(dfsC, c, sizeof(c)); //store origin string
    ans[0] = '9'+ 1; //initial max value
    for(maxD = 1;; maxD++) {
        bool ok = false;
        for(int i = 0; i < tCnt; i++) {
            iChoose = i;
            memcpy(c,dfsC,sizeof(c));
            if(dfs(0, la + lb + lc + 1)) {
                update(c);
                ok = true;
            }
        }
        if(ok) return;
    }
}
int main()
{
    int kase = 0;
    while(gets(c) != NULL && c[0] != '0') {
        memcpy(ans, c, sizeof(ans));
        bool valid = search();
        if(valid && tCnt > 1) {
            specialize();
        }
        printf("Case %d: ", ++kase);
        printf("%s\n", ans);
    }
}