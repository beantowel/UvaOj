#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
#define tprintf //printf
const int findc[7][7] = {
{0,0,0,0,0,0,0},
{0,0,4,2,5,3,0},
{0,3,0,6,1,0,4},
{0,5,1,0,0,6,2},
{0,2,6,0,0,1,5},
{0,4,0,1,6,0,3},
{0,0,3,5,2,4,0}
}; //find c by a,b --> clockwise search
const int oppo[] = {0,6,5,4,3,2,1};
                    //1,2,3,4,5,6
typedef struct _Node {
    int a, b; //a front, b top
    int x, y;
    int pre;
    _Node Up(){
        x = x - 1;
        int t = b;
        b = a;
        a = oppo[t];
    }
    _Node Down(){
        x = x + 1;
        int t = a;
        a = b;
        b = oppo[t];
    }
    _Node Right(){
        y = y + 1;
        int t = findc[a][b];
        b = oppo[t];
    }
    _Node Left(){
        y = y - 1;
        int t = findc[a][b];
        b = t;
    }
} Node, *PNode;

const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int maze[12][12];
int mazeVis[12][12]; //mazeVis = (1 << front value) | (1 << top value)
char str[25];
int mazeN = 0;
int r, c, sx, sy, sb, sa, ansD;
vector<Node> q;

void Tip(Node *n, int dir){
    switch(dir){
        case 0:
            n->Up();
            break;
        case 1:
            n->Right();
            break;
        case 2:
            n->Down();
            break;
        case 3:
            n->Left();
    }
}
bool Valid(Node *n, int b){
    int m = maze[n->x][n->y];
    if(m != -1 && m != b) return false; //not match
    int vis = 1 << (n->a - 1);
    vis |= 1 << (n->b + 7); //byte0 |a, byte1 |b
    if((mazeVis[n->x][n->y] & vis) == vis) return false; //visted
    return true;
}
void Bfs(){
    q.clear();
    Node start;
    start.x = sx;
    start.y = sy;
    start.b = sb;
    start.a = sa;
    start.pre = -1;
    q.push_back(start);
    int head = 0;
    while(head != q.size()){
        Node node = q[head];
        int x = node.x;
        int y = node.y;
        tprintf("pop:\n");
        tprintf("x:%d,y:%d,b:%d,a:%d,pre:x:%d,y:%d\n", x, y, node.b, node.a);
        if(x == sx && y == sy && node.pre != -1){
            tprintf("possible\n");
            int cur = head;
            stack<int> s;
            while(cur != -1){
                tprintf("x:%d,y:%d\n", q[cur].x, q[cur].y);
                s.push(cur);
                cur = q[cur].pre;
            }
            int cnt = 0;
            printf("  ");
            while(!s.empty()){
                int t = s.top(); s.pop();
                if(cnt % 9) printf(","); //not TOL
                if(cnt % 9 == 0 && cnt > 0) printf(",\n  "); //1+ TOL
                printf("(%d,%d)", q[t].x, q[t].y);
                cnt++;
            }
            printf("\n");
            return;
        }
        tprintf("push:\n");
        for(int i=0;i<4;i++){
            if(maze[x+dx[i]][y+dy[i]]){ //not out of range
                Node t = node;
                Tip(&t, i);
                t.pre = head;
                if(Valid(&t ,node.b)){
                    tprintf("x:%d,y:%d,dir:%d,pre:x:%d,y:%d\n", \
                        t.x, t.y, i, q[t.pre].x, q[t.pre].y);
                    mazeVis[t.x][t.y] |= 1 << (t.a - 1);
                    mazeVis[t.x][t.y] |= 1 << (t.b + 7); //set flag
                    q.push_back(t);
                }
            }
        }
        head++;
    }
    printf("  No Solution Possible\n");
}
int main()
{
    while(~scanf("%s", str) && strcmp(str, "END")) {
        mazeN++;
        scanf("%d%d%d%d%d%d", &r, &c, &sx, &sy, &sb, &sa);
        memset(maze, 0, sizeof(maze));
        memset(mazeVis, 0, sizeof(mazeVis));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++)
                scanf("%d", &maze[i+1][j+1]);
            scanf("\n");
        }
        printf("%s\n", str);
        Bfs();
    }
    return 0;
}