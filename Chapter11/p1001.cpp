#include <cstdio>
#include <cstring>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000.0;
const int N = 102;
struct Node {
    int x, y, z, r;
    Node(int xx = 0, int yy = 0, int zz = 0, int rr = 0): x(xx), y(yy), z(zz), r(rr) {}
    double Dis(Node &v)
    {
        double dis = (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z);
        dis = sqrt(dis);
        dis -= (r + v.r);
        dis = dis > 0 ? dis : 0;
        return dis;
    }
};
int n;
double d[N], edge[N][N];
vector<Node> nodes;
int cnt[N];
bool inq[N];
bool BellmanFord(int s, int t)
{
    for(int i = 0; i < n; i++)
        d[i] = INF;
    queue<int> Q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    d[s] = 0;
    inq[s] = true;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for(int i = 0; i < n; i++)
            if(d[u] < INF && d[i] > d[u] + edge[u][i]) {
                d[i] = d[u] + edge[u][i];
                //p[i]=u;
                if(!inq[i]) {
                    Q.push(i);
                    inq[i] = true;
                    // if(++cnt[i]>n) return false; //不存在的
                }
            }
    }
}
int main()
{
    int kase = 0;
    while(scanf("%d\n", &n) && n != -1) {
        nodes.clear();
        int x, y, z, r;
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &x, &y, &z, &r);
            nodes.push_back(Node(x, y, z, r));
        }
        for(int i = 0; i < 2; i++) {
            scanf("%d%d%d", &x, &y, &z);
            nodes.push_back(Node(x, y, z, 0));
        }
        n += 2;
        for(int i = 0; i < n; i++) {
            edge[i][i] = 0;
            for(int j = i + 1; j < n; j++) {
                edge[i][j] = nodes[i].Dis(nodes[j]);
                edge[j][i] = edge[i][j];
            }
        }
        BellmanFord(n-2,n-1);
        printf("Cheese %d: Travel time = %.0f sec\n", ++kase, 10 * d[n-1]);
    }
    return 0;
}