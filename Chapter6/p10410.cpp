#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 1000;
int bfs[maxn], dfs[maxn], l[maxn], r[maxn], n;
vector<int> child[maxn + 1];
int main() {
    while(scanf("%d", &n) > 0) {
        for(int i = 0; i < n; i++) scanf("%d", &bfs[i]);
        for(int i = 0; i < n; i++) {
            scanf("%d", &dfs[i]);
            child[i + 1].clear();
        }
        memset(child, 0, sizeof(child));
        memset(l, 0, sizeof(l)); //left/right interval for dfs
        memset(r, 0, sizeof(r));
        queue<int> q;
        q.push(0); //idx==0
        l[0] = 0;
        r[0] = n;
        int idx = 1;
        while(!q.empty()) {
            int node = q.front(); q.pop();
            //printf("l:%d r:%d :node%d\n", l[node], r[node], bfs[node]);
            bool b = false;
            for(int i = l[node]; i < r[node] && idx < n; i++) {
                if(dfs[i] == bfs[idx]) {
                    if(b) r[idx - 1] = i;
                    b = true; //first flag
                    l[idx] = i;
                    child[bfs[node]].push_back(bfs[idx]);
                    q.push(idx++);
                    if(b && bfs[idx] < bfs[idx - 1]) break; //ascending order
                }
            }
            if(b) r[idx - 1] = r[node];
            //printf("r[%d]=r[%d]=%d\n", bfs[idx - 1], bfs[node], r[node]);
        }
        for(int i = 1; i < n + 1; i++) {
            printf("%d:", i);
            for(int j = 0; j < child[i].size(); j++) {
                printf(" %d", child[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}