#include <cstdio>
#include <cstring>

const int N = 10;
int n, m, depth;
char mat[N][N];
char queen[N][N];
bool check()
{
    // printf("check %d\n", depth);
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         printf("%d ", queen[i][j]);
    //     }
    //     printf("\n");
    // }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(mat[i][j] && (!queen[i][j])) return false;
    return true;
}
void place(int x, int y)
{
    for(int i = 0; i < n; i++)
        queen[i][y] = 1;
    for(int j = 0; j < m; j++)
        queen[x][j] = 1;
    int t1 = x + y, t2 = x - y;
    for(int i = 0; i < n; i++) {
        if(t1 - i >= 0 && t1 - i < m) queen[i][t1 - i] = 1;
        if(i - t2 >= 0 && i - t2 < m) queen[i][i - t2] = 1;
    }
}
bool dfs(int d, int x, int y)
{
    if(d == depth) {
        return check();
    }
    char temp[N][N];
    memcpy(temp, queen, sizeof(temp));
    int i=x, j=y;
    while(i<n){
        // printf("x:%d y:%d\n", i, j);
        place(i, j);
        i+=(j+1) / m;
        j=(j+1) % m;
        if(dfs(d + 1, i, j)) return true;
        memcpy(queen, temp, sizeof(temp));
    }
    return false;
}
int main()
{
    char s[20];
    int kase = 0;
    while(scanf("%d %d\n", &n, &m) && n != 0) {
        memset(mat, 0, sizeof(mat));
        for(int i = 0; i < n; i++) {
            gets(s);
            for(int j = 0; j < m; j++) {
                if(s[j] == 'X')
                    mat[i][j] = 1;
                // printf("%d ", mat[i][j]);
            }
            // printf("\n");
        }
        depth = 0;
        memset(queen, 0, sizeof(queen));
        while(depth < 5 && !dfs(0, 0, 0)) {
            depth++;
            memset(queen, 0, sizeof(queen));
        }
        printf("Case %d: %d\n", ++kase, depth);
    }
    return 0;
}