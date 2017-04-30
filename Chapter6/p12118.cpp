#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int V, E, T;
short map[1000][1000]; //undirected
int vis[1000];
int degree[1000];
int odd[1000], flag[1000];
void CntCompo()
{
    int cnt = 0;
    memset(vis, -1, sizeof(vis));
    for(int i = 0; i < V; i++) {
        if(vis[i] >= 0) continue;
        queue<int> q;
        q.push(i);
        vis[i] = cnt;
        // printf("push%d,vis:%d\n", i, cnt);
        while(!q.empty()) {
            int n = q.front(); q.pop();
            for(int j = 0; j < V; j++)
                if(map[n][j] && vis[j] == -1) {
                    q.push(j);
                    vis[j] = cnt;
                }
        }
        cnt++;
    }
}
int CntVertex()
{
    int oddCnt = 0;
    memset(odd, 0, sizeof(odd));
    memset(degree, 0, sizeof(degree));
    memset(flag, 0, sizeof(flag));
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            if(map[i][j]) degree[i]++;
    for(int i = 0; i < V; i++) {
        if(degree[i] == 0) {
            odd[vis[i]] = -1;
            continue;
        }
        if(degree[i] % 2 == 1) {
            odd[vis[i]]++;
            oddCnt++;
        }
        flag[vis[i]] = 1;
    }
    return oddCnt;
}
int main()
{
    int kase = 0;
    while(~scanf("%d%d%d", &V, &E, &T) && !(V == 0 && E == 0 && T == 0)) {
        memset(map, 0, sizeof(map));
        for(int i = 0; i < E; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            map[u - 1][v - 1] = 1;
            map[v - 1][u - 1] = 1;
        }
        //components count
        CntCompo();
        int x = CntVertex() / 2;
        int c = -1;
        for(int i = 0; i < 1000; i++)
            if(flag[i]) c++;
        // for(int i = 0; i < V; i++)
        //     printf("vis[%d]:%d ", i, vis[i]);
        // printf("\n");
        int temp = x >= c ? x - c : c - x;
        int y = temp > 1 ? temp - 1 : 0;
        int ans = (E + c + y) * T;
        if(c == -1) ans = 0;
        // printf("x:%d,c:%d,y:%d,E:%d\n", x, c, y, E);
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}