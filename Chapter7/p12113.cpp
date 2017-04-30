#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 6, n = 4, nSquare = 6;
const int dx[] = { -1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int special1[n][n] = {
    {0, 0, 1, 1},
    {0, 2, 1, 1},
    {3, 3, 4, 0},
    {3, 3, 0, 0},
};
const int special2[n][n] = {
    {1, 1, 0, 0},
    {1, 1, 2, 0},
    {0, 3, 4, 4},
    {0, 0, 4, 4},
};
int block[n][n], valid[n][n], t[n][n], vis[n][n];
int cnt, maxD;
void init(char *c)
{
    int edge[N * N][N * N];
    int tBlk[N * N][N * N];
    memset(edge, 0, sizeof(edge));
    memset(tBlk, -1, sizeof(tBlk));
    memset(valid, 0, sizeof(valid));
    for(int j = 0; j < n; j++) {
        if(c[2 * j + 1] == '_') {
            edge[j + 1][j + N + 1] = 1;
            edge[j + N + 1][j + 1] = 1;
        }
    }
    for(int i = 1; i < (n + 1); i++) {
        gets(c);
        for(int j = 0; j < (n + 1); j++) {
            if(c[2 * j] == '|') {
                edge[N * i + j][N * i + j + 1] = 1;
                edge[N * i + j + 1][N * i + j] = 1;
            }
        }
        for(int j = 0; j < n; j++) {
            if(c[2 * j + 1] == '_') {
                edge[N * i + j + 1][N * (i + 1) + j + 1] = 1;
                edge[N * (i + 1) + j + 1][N * i + j + 1] = 1;
            }
        }
    }
    cnt = -1; //flood block
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(tBlk[i][j] == -1) {
                queue<int> q;
                int color = ++cnt;
                q.push(i * N + j);
                tBlk[i][j] = color;
                while(!q.empty()) {
                    int t = q.front(); q.pop();
                    int y = t % N;
                    int x = t / N;
                    for(int k = 0; k < 4; k++) {
                        int x1 = x + dx[k];
                        int y1 = y + dy[k];
                        if(x1 >= 0 && x1 < N && y1 >= 0 && y1 < N && tBlk[x1][y1] == -1) {
                            int t1 = x1 * N + y1;
                            if(edge[t][t1]) continue;
                            q.push(x1 * N + y1);
                            tBlk[x1][y1] = color;
                        }
                    }
                }
            }
    //copy to block
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            block[i][j] = tBlk[i + 1][j + 1];
            // printf("%2d ", block[i][j]);
        }
        // printf("\n");
    }
    //one special situation:
    /*
         _ _ #
       _|   |#
     _|_|_ _|#
    |   |_|  #
    |_ _|    #
    */
    //violently handle it
    if(cnt == 4) {
        if(memcmp(block, special1, sizeof(block)) == 0) {
            cnt = 3;
            block[2][2] = 2;
        };
        if(memcmp(block, special2, sizeof(block)) == 0) {
            cnt = 3;
            block[2][1] = 2;
        }
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(block[i][j] && block[i + 1][j + 1] && block[i + 1][j] && block[i][j + 1]) {
                valid[i][j] = 1 << block[i][j];
                valid[i][j] |= 1 << block[i + 1][j];
                valid[i][j] |= 1 << block[i][j + 1];
                valid[i][j] |= 1 << block[i + 1][j + 1];
            }
        }
    }
}
bool judge()
{
    int cast[100]; //cast from t to vs
    //injective relationship
    memset(cast, -1, sizeof(cast));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(block[i][j] != 0 && t[i][j] == 0) return false;
            if(cast[t[i][j]] == -1) {
                cast[t[i][j]] = block[i][j];
            } else if(cast[t[i][j]] != block[i][j])
                return false;
        }
    return true;
}
void dye(int i, int j, int c)
{
    t[i][j] = c;
    t[i + 1][j] = c;
    t[i][j + 1] = c;
    t[i + 1][j + 1] = c;
}
bool dfs(int d)
{
    if(d == maxD)
        return judge();
    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - 1; j++) {
            if(valid[i][j] && !vis[i][j]) {
                vis[i][j] = 1;
                int preT[n][n];
                memcpy(preT, t, sizeof(t));

                int k = valid[i][j];
                int color = 0;
                while(k > 0) {
                    k = k >> 1;
                    color++;
                    if(k & 0x1) {
                        dye(i, j, color);
                        if(dfs(d + 1)) return true;
                    }
                }

                memcpy(t, preT, sizeof(t));
                vis[i][j] = 0;
            }
        }
    return false;
}
int main()
{
    char c[20];
    int kase = 0;
    int ans;
    while(gets(c) != NULL && c[0] != '0') {
        ans = 0;
        init(c);
        if(cnt <= nSquare) {
            memset(t, 0, sizeof(t));
            memset(vis, 0, sizeof(vis));
            maxD = cnt;
            ans = dfs(0);
        }
        printf("Case %d: ", ++kase);
        if(ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}