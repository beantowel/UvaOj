#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 102;
const int INF = 1000000000;
struct Edge {
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f = 0): from(u), to(v), cap(c) , flow(f) {}
};
struct MF {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    int vis[maxn];
    int a[maxn];
    int p[maxn];
    void init(int n)
    {
        for(int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
    }
    void AddEdge(int u, int v, int c)
    {
        edges.push_back(Edge(u, v, c, 0));
        edges.push_back(Edge(v, u, c, 0)); //???
        m = edges.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }
    bool BFS(int s, int t, int &flow)
    {
        memset(vis, 0, sizeof(vis));
        a[s] = INF; p[s] = -1;
        a[t] = 0;
        queue<int> Q;
        Q.push(s);
        vis[s] = 1;
        // printf("BFS\n");
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            // printf("u:%d\n", u+1);
            for(int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if(e.cap > e.flow && !vis[e.to]) {
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(e.to==t) break;
                    if(!vis[e.to]) {
                        Q.push(e.to);
                        vis[e.to] = 1;
                    }
                }
            }
        }
        if(a[t]==0) return false;
        flow+=a[t];
        for(int u=t; u!=s; u=edges[p[u]].from){
            // printf("u=%d\n", u+1);
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
        }
        return true;
    }
    int MaxFlow(int s,int t){
        int flow=0;
        while(BFS(s,t,flow));
        return flow;
    }
};
int n, s, t, cnt;
MF g;
int main()
{
    int kase=0;
    while(scanf("%d\n", &n) && n) {
        g.init(n);
        scanf("%d%d%d", &s, &t, &cnt);
        s--; t--;
        int u, v, c;
        for(int i = 0; i < cnt; i++) {
            scanf("%d%d%d\n", &u, &v, &c);
            g.AddEdge(u-1,v-1,c);
        }
        int ans=g.MaxFlow(s,t);
        printf("Network %d\n", ++kase);
        printf("The bandwidth is %d.\n\n", ans);
    }
    return 0;
}