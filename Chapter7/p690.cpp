#include <cstdio>
#include <cstring>
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)<(b) ? (b) : (a))
const int N = 5, M = 10;
int task[N], offset[M] , jump[100];
int n, ans, idx;
char c[30];

bool judge(int *w, int j)
{
    for(int i = 0; i < N; i++) {
        if(task[i] & (w[i] >> j)) return false;
    }
    return true;
}
void dfs(int sum, int d, int *w)
{
    if(d == 10) {
        ans = min(ans, sum);
        return;
    }
    if((sum + (M - d) * jump[0]) >= ans) return;
    int tW[N];
    for(int i = 0; i < idx; i++) {
        if(!judge(w, jump[i])) continue;
        for(int j = 0; j < N; j++) {
            tW[j] = w[j] >> jump[i];
            tW[j] |= task[j];
        }
        offset[d] = jump[i];
        dfs(sum + jump[i], d + 1, tW);
    }
}
void init()
{
    memset(task, 0, sizeof(task));
    memset(jump, 0, sizeof(jump));
    for(int i = 0; i < N; i++) {
        scanf("%s", c);
        for(int j = 0; j < n; j++)
            if(c[j] == 'X') {
                task[i] |= 1 << j;
            }
    }
    idx = 0;
    for(int i = 1; i < n + 1; i++) {
        if(judge(task, i)) jump[idx++] = i;
    }
}
int main()
{
    while(~scanf("%d", &n) && n != 0) {
        init();
        ans = n * M;
        dfs(n, 1, task);
        printf("%d\n", ans);
    }
    return 0;
}