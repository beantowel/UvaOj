#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1000;
int bfs[maxn], dfs[maxn], bfsDepth[maxn], n;
int dfsIdxToBfs[maxn];
vector<int> child[maxn];
void updateDepth(int idx, int d) {
    for(int i = idx; i < n; i++)
        bfsDepth[i] = bfsDepth[i] < d ? d : bfsDepth[i];
}
int Dfs(int dfs_idx, int d) {
    //input node idx,return last branch idx
    int bfs_idx=dfsIdxToBfs[dfs_idx];
    if(bfsDepth[bfs_idx] < d || dfs_idx >= n)
        return dfs_idx;
    updateDepth(bfs_idx, d);

    int next = dfs_idx + 1;
    while(next < n) {
        next = Dfs(next, d + 1);
    }
}
int main() {
    scanf("%d", n);
    for(int i = 0; i < n; i++) scanf("%d", &bfs[i]);
    for(int i = 0; i < n; i++) {
        scanf("%d", &dfs[i]);
        for(int j = 0; j < n; j++)
            if(bfs[j] == dfs[i]) {
                dfsIdxToBfs[i] = j;
                break; //Generate dfs Index to bfs Index cast
            }
    }
    memset(bfsDepth, 0, sizeof(bfsDepth));
    Dfs(0, 0);
    return 0;
}