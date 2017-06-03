#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int R = 100, C = 100;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int N, r, c, ans;
int m[R][C];
int h[R][C];
int dp(int x, int y)
{
    if(h[x][y] != -1) return h[x][y];
    int t = 1;
    for(int k = 0; k < 4; k++) {
        int i = x + dx[k];
        int j = y + dy[k];
        if(i >= 0 && i < r && j >= 0 && j < c && m[i][j] < m[x][y])
            t = max(t, dp(i,j) + 1);
    }
    h[x][y] = t;
    return t;
}
int main()
{
    scanf("%d\n", &N);
    while(N--) {
        char s[50];
        scanf("%s%d%d\n", s, &r, &c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++)
                scanf("%d", &m[i][j]);
            scanf("\n");
        }
        ans = 0;
        memset(h, -1, sizeof(h));
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                ans = max(ans, dp(i, j));
        // for(int i = 0; i < r; i++) {
        //     for(int j = 0; j < c; j++) {
        //         printf("%d ", h[i][j]);
        //     }
        //     printf("\n");
        // }
        printf("%s: %d\n", s, ans);
    }
    return 0;
}