#include <cstdio>
#include <cstring>
#include <cstdlib>

const int maxRange = 250;
const char dir[] = {'n', 'e', 's', 'w'};
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const int chdir[] = {1, 0, 2, 3};
int mX[2 * maxRange][2 * maxRange], mY[2 * maxRange][2 * maxRange]; //culmulated cnt
short vis[2 * maxRange][2 * maxRange];
int path[30];
int len, n, cnt;

// void DebugPrint()
// {
//     int x = 0, y = 0;
//     for(int i = 0; i < len; i++) {
//         printf("(%d,%d)->", x, y);
//         x += (i + 1) * dx[path[i]];
//         y += (i + 1) * dy[path[i]];
//     }
//     printf("(%d,%d)", x, y);
//     printf("\n");
// }
void Dfs(int x, int y, int d)
{
    // printf("x:%d,y:%d,l:%d,len:%d\n", x - maxRange, y - maxRange, d + 1, len);
    if(d == len && x == maxRange && y == maxRange) {
        cnt++;
        for(int i = 0; i < len; i++)
            printf("%c", dir[path[i]]);
        printf("\n");
        // DebugPrint();
    }
    if(d > len) return;
    int maxS = (d + 1 + len) * (len - d) / 2;
    if(abs(x - maxRange) + abs(y - maxRange) > maxS) return; //pruning
    for(int ii = 0; ii < 4; ii++) {
        int i = chdir[ii];
        if(d == 0 || (path[d - 1] != i && path[d - 1] != (i + 2) % 4)) {
            int x1 = x + (d + 1) * dx[i];
            int y1 = y + (d + 1) * dy[i];
            int delta = (dy[i] == 0) ? mX[x1][y1] - mX[x][y] : mY[x1][y1] - mY[x][y];
            // printf("x:%d,y:%d-->x1:%d,y1:%d,delta:%d\n",\
            //     x-maxRange,y-maxRange,x1-maxRange,y1-maxRange, delta);
            if(x1 < 0 || x1 >= 2 * maxRange || y1 < 0 || y1 >= 2 * maxRange) continue;
            if(delta == 0 && vis[x1][y1] == 0) {
                path[d] = i;
                vis[x1][y1] = 1;
                Dfs(x1, y1, d + 1);
                vis[x1][y1] = 0;
            }
        }
    }
}
int main()
{
    int kase;
    scanf("%d", &kase);
    while(kase--) {
        memset(mX, 0, sizeof(mX));
        memset(mY, 0, sizeof(mY));
        memset(vis, 0, sizeof(vis));
        len = 0;
        n = 0;
        scanf("%d", &len);
        scanf("%d", &n);
        // printf("kase:%d,len:%d,n:%d\n", kase+1, len, n);
        int x, y;
        for(int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            x += maxRange;
            y += maxRange;
            if(x >= 0 && x < 2 * maxRange && y >= 0 && y < 2 * maxRange) {
                for(int j = x; j < 2 * maxRange; j++) mX[j][y] += 2;
                for(int j = y; j < 2 * maxRange; j++) mY[x][j] += 2;
                mX[x][y]--;
                mY[x][y]--;
            }
        }
        cnt = 0;
        Dfs(maxRange, maxRange, 0);
        printf("Found %d golygon(s).\n\n", cnt);
    }
    return 0;
}