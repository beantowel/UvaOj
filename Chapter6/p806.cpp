#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m[64][64];
int a[4100];
int n, cnt, kase = 0;
int dx[4] = {0, 0, 1, 1};
int dy[4] = {0, 1, 0, 1};
const int BASE = 5;
int GetColor(int x, int y, int len) {
    bool white = true, black = true;
    for(int i = x; i < x + len; i++)
        for(int j = y; j < y + len; j++) {
            black = (m[i][j] ? true : false) && black;
            white = (m[i][j] ? false : true) && white;
            if(!white && !black) return -1;
        }
    if(black) return 1;
    if(white) return 0;
}
void IMGdfs(int x, int y, int len, int path) {
    int color = GetColor(x, y, len);
    if(color >= 0) {
        if(color == 1) a[cnt++] = path;
        return;
    }
    len = len / 2;
    for(int i = 0; i < 4; i++) {
        int x1, y1;
        x1 = x + dx[i] * len;
        y1 = y + dy[i] * len;
        IMGdfs(x1, y1, len, path * BASE + i + 1);
    }
}
void PrintPath() {
    const int NODES = 12;
    int nodes = 0;
    sort(a, a + cnt);
    for(int i = 0; i < cnt; i++) {
        if(nodes % NODES) printf(" ");
        printf("%d", a[i]);
        if((++nodes) % NODES == 0) printf("\n");
    }
    if(nodes % NODES != 0) printf("\n");
    printf("Total number of black nodes = %d\n", cnt);
}
void ConvertPath() {
    for(int i = 0; i < cnt; i++) {
        int before = a[i], after = 0;
        while(before > 0) {
            int bit = before % BASE;
            after = after * BASE + bit;
            before = before / BASE;
        }
        a[i] = after;
    }
}
void Color(int x, int y, int len) {
    for(int i = x; i < x + len; i++)
        for(int j = y; j < y + len; j++)
            m[i][j] = 1;
}
void Pathdfs() {
    if(!cnt) return;
    for(int i = 0; i < cnt; i++) {
        int path = a[i], len = n, x = 0, y = 0;
        while(path > 0) {
            int branch = path % BASE;
            path = path / BASE;
            len = len / 2;
            x = x + dx[branch - 1] * len;
            y = y + dy[branch - 1] * len;
        }
        Color(x, y, len);
    }
}
void PrintIMG() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%c", m[i][j] == 1 ? '*' : '.');
        printf("\n");
    }
}
int main() {
    while(scanf("%d\n", &n) != -1 && n) {
        if(kase) printf("\n");
        printf("Image %d\n", ++kase);
        memset(m, 0, sizeof(m));
        cnt = 0;
        if(n > 0) {
            char c;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    scanf("%c", &c);
                    m[i][j] = (c == '1') ? 1 : 0;
                }
                scanf("\n");
            }
            IMGdfs(0, 0, n, 0);
            ConvertPath();
            PrintPath();
        } else {
            n = -n;
            int d = -1;
            while(scanf("%d", &d) && d != -1)
                a[cnt++] = d;
            Pathdfs();
            PrintIMG();
        }
    }
    return 0;
}