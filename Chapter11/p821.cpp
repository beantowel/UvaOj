#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
const int N = 110;

int d[N][N];
int node[N];
int n;

void Floyd()
{
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main()
{
    int u, v, kase = 0;
    float ans;
    while(scanf("%d %d", &u, &v) && u && v) {
        n = 0;
        memset(d, -1, sizeof(d));
        memset(node, -1, sizeof(node));
        do {
            if(node[u] == -1) node[u]=n++;
            if(node[v] == -1) node[v]=n++;
            d[node[u]][node[v]] = 1;
        } while(scanf("%d %d", &u, &v) && u && v);
        for(int i = 0; i < n; i++) {
            d[i][i] = 0;
            for(int j=0; j<n; j++){
                if(d[i][j]==-1) d[i][j]=INF;
            }
        }

        Floyd();
        long long cnt = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                // printf("%d ", d[i][j]);
                cnt += d[i][j];
            }
            // printf("\n");
        }
        ans = float(cnt) / n / (n - 1);
        printf("Case %d: average length between pages = %.3f clicks\n", ++kase, ans);
    }
    return 0;
}