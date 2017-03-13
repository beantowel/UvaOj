#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
int a[20][20], vis[20][20];
int n, m, k;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
struct Node {
    int x, y, cros, len;
    Node(int x, int y, int cros, int len): x(x), y(y), cros(cros), len(len) {}
};
void bfs() {
    Node root(0, 0, 0, 0);
    queue<Node> q;
    q.push(root);
    while(!q.empty()) {
        Node front = q.front(); q.pop();
        if(front.x == n - 1 && front.y == m - 1) {
            cout << front.len << endl;
            return;
        }
        for(int i = 0; i < 4; i++) {
            int x = front.x, y = front.y;
            x += dx[i]; y += dy[i];
            if(x >= 0 && y >= 0 && x < n && y < m) {
                int cros = front.cros;
                if(a[x][y]) cros++;
                else cros=0;
                if(cros < vis[x][y]) {
                    vis[x][y] = cros;
                    //printf("x:%d y:%d c:%d len:%d vis:%d\n", x, y, cros, front.len + 1, vis[x][y]);
                    q.push(Node(x, y, cros, front.len + 1));
                }
            }
        }
    }
    cout << "-1\n";
}
int main() {
    int kase;
    cin >> kase;
    while(kase--) {
        cin >> n >> m >> k;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                cin >> a[i][j];
                vis[i][j] = k + 1;
            }
        bfs();
    }
}