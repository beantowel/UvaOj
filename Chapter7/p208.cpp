#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
short map[20][20];
short vis[20], dfsVis[20], list[20];
int des, N, cnt;
int Connected()
{
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while(!q.empty()) {
        int n = q.front(); q.pop();
        // printf("pop:%d\n", n+1);
        for(int i = 0; i < N; i++) {
            if((!vis[i]) && map[n][i]) {
                vis[i] = 1;
                q.push(i);
                // printf("push:%d\n", i+1);
            }
        }
    }
    return vis[des];
}
void Dfs(int n, int d)
{
    if(n == des) {
        for(int i = 0; i < d; i++)
            printf("%d ", list[i] + 1);
        printf("%d\n", des + 1);
        cnt++;
        return;
    }
    dfsVis[n] = 1;
    list[d] = n;
    // printf("dfs:%d,depth:%d\n", n,d);
    for(int i = 0; i < N; i++) {
        if(vis[i] && (!dfsVis[i]) && map[n][i]) {
            Dfs(i, d + 1);
        }
    }
    dfsVis[n] = 0;
}
int main()
{
    int kase = 0;
    while(~scanf("%d", &des)) {
        des -= 1;
        memset(map, 0, sizeof(map));
        int u, v;
        N = 0;
        while(scanf("%d%d", &u, &v) == 2 && u != 0 && v != 0) {
            map[u - 1][v - 1] = 1;
            map[v - 1][u - 1] = 1;
            N = u > N ? u : N;
            N = v > N ? v : N;
        }
        printf("CASE %d:\n", ++kase);
        cnt = 0;
        if(Connected()) {
            memset(dfsVis, 0, sizeof(dfsVis));
            memset(list, 0, sizeof(list));
            Dfs(0, 0);
        }
        printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, des + 1);
    }
    return 0;
}