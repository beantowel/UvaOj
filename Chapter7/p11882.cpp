#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int R = 31, C = 31;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
struct point {
    int x;
    int y;
    point(int xx, int yy): x(xx), y(yy) {};
};

int r, c;
int mat[R][C];
int maxlen, ans[R * C];
char vis[R][C];
int arr[R * C];
int conn[R][C], connlen[R * C];

bool aBEb(int *a, int *b, int len)
{
    for(int i = 0; i <= len; i++) {
        if(a[i] < b[i]) return false;
        if(a[i] > b[i]) break;
    }
    return true;
}
bool prune(int x, int y, int len)
{
    // printf("connlen:%d maxlen:%d\n", connlen[conn[x][y]],maxlen);
    if(connlen[conn[x][y]] < maxlen) return true;
    if(connlen[conn[x][y]] == maxlen && !aBEb(arr, ans, len)) return true;
    char bfsVis[R][C];
    memset(bfsVis, 0, sizeof(bfsVis));
    int cnt = 0;
    queue<point> q;
    q.push(point(x, y));
    bfsVis[x][y] = 1;
    while(!q.empty()) {
        point p = q.front(); q.pop();
        cnt++;
        for(int k = 0; k < 4; k++) {
            int i = p.x + dx[k];
            int j = p.y + dy[k];
            // printf("mat:%d vis:%d bfsVis:%d\n", mat[i][j],vis[i][j],bfsVis[i][j]);
            if(i >= 0 && j >= 0 && mat[i][j] > 0 && !vis[i][j] && !bfsVis[i][j]) {
                q.push(point(i, j));
                bfsVis[i][j] = 1;
            }
        }
    }
    if(cnt + len < maxlen) {
        // for(int i=0;i<=len;i++)
        //     printf("%d ", arr[i]);
        // printf("\ncnt:%d len:%d maxlen:%d x:%d y:%d\n",cnt,len,maxlen,x,y);
        return true;
    }
    if(cnt + len == maxlen && !aBEb(arr, ans, len)) return true;
    return false;
}
void dfs(int x, int y, int len)
{
    arr[len] = mat[x][y];
    vis[x][y] = 1;
    if(prune(x, y, len)) {
        vis[x][y] = 0;
        return;
    }
    int flag = 0;
    for(int k = 0; k < 4; k++) {
        int i = x + dx[k];
        int j = y + dy[k];
        if(i >= 0 && j >= 0 && mat[i][j] > 0 && !vis[i][j]) {
            dfs(i, j, len + 1);
            flag = 1;
        }
    }
    vis[x][y] = 0;
    if(flag) return;
    if(len == maxlen && aBEb(arr, ans, len))
        memcpy(ans, arr, sizeof(int) * (len + 1));
    if(len > maxlen) {
        maxlen = len;
        memcpy(ans, arr, sizeof(int) * (len + 1));
    }
}
void floodfill()
{
    memset(conn, -1, sizeof(conn));
    memset(connlen, 0, sizeof(conn));
    int compo = 0;
    for(int ii = 0; ii < r; ii++)
        for(int jj = 0; jj < c; jj++)
            if(mat[ii][jj] > 0 && conn[ii][jj] == -1) {
                int cnt = 0;
                queue<point> q;
                q.push(point(ii, jj));
                conn[ii][jj] = compo;
                while(!q.empty()) {
                    point p = q.front(); q.pop();
                    cnt++;
                    for(int k = 0; k < 4; k++) {
                        int i = p.x + dx[k];
                        int j = p.y + dy[k];
                        if(i >= 0 && j >= 0 && mat[i][j] > 0 && conn[i][j] == -1) {
                            q.push(point(i, j));
                            conn[i][j] = compo;
                        }
                    }
                }
                connlen[compo++] = cnt-1;
            }
    // for(int i = 0; i < r; i++) {
    //     for(int j = 0; j < c; j++) {
    //         printf("%d ", conn[i][j]);
    //     }
    //     printf("\n");
    // }
    // for(int i=0;i<compo;i++)
    //     printf("%d ", connlen[i]);
    // printf("\n");
}
int main()
{
    char str[40];
    while(~scanf("%d %d\n", &r, &c) && r && c) {
        memset(mat, -1, sizeof(mat));
        for(int i = 0; i < r; i++) {
            gets(str);
            for(int j = 0; j < c; j++) {
                mat[i][j] = str[j] - '0';
                if(str[j] == '#') mat[i][j] = -1;
                // printf("%3d", mat[i][j]);
            }
            // printf("\n");
        }
        floodfill();
        maxlen = -1;
        memset(ans, 0, sizeof(ans));
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                if(mat[i][j] > 0) {
                    memset(vis, 0, sizeof(vis));
                    dfs(i, j, 0);
                }
        for(int i = 0; i <= maxlen; i++)
            printf("%d", ans[i]);
        // printf("\nlen:%d\n", maxlen);
        printf("\n");
    }
    return 0;
}