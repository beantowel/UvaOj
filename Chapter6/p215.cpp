#include <cstdio>
#include <cstring>
const int R = 20, C = 10;
int r, c;
int sheet[R * C];
int vis[R * C];
char expre[R * C][80];
short mSign[R * C][R * C];
short map[R*C][R*C];
int HandlePoint(char *c, int vertex)
{
    while(c[0] != ' ' && c[0] != '\0') {
        int sign = 1;
        if(c[0] == '-') { //minus sign
            sign = -1;
            c = c + 1;
        } else if(c[0] == '+') //plus sign
            c++;
        if(c[0] <= '9' && c[0] >= '0') { //constant
            int t = 0;
            while(c[0] <= '9' && c[0] >= '0') {
                t = t * 10 + (c[0] - '0');
                c++;
            }
            sheet[vertex] += sign * t;
            continue;
        }
        int v = (c[0] - 'A') * C + (c[1] - '0'); //cell
        map[v][vertex] = 1;
        mSign[v][vertex] += sign; //u->v, outdegree
        c += 2;
    }
}
int CountIndegree(int vertex)
{
    int cnt = 0;
    for(int i = 0; i < R * C; i++)
        if(map[i][vertex]) cnt++;
    return cnt;
}
void UpdateDegree(int vertex)
{
    for(int i = 0; i < R * C; i++)
        if(mSign[vertex][i]) {
            sheet[i] += mSign[vertex][i] * sheet[vertex]; //update value
        }
    memset(map[vertex], 0, sizeof(map[vertex])); //clear edge
}
bool Solve()
{
    bool b = true;
    while(b) {
        b = false; //flag
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++) { //traverse all vertex
                int vertex = i * C + j;
                int cnt = CountIndegree(vertex);
                if(cnt == 0 && (!vis[vertex])) { //0-indegree vertex
                    b = true;
                    vis[vertex] = 1;
                    UpdateDegree(vertex);
                }
            }
    }
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++) //traverse all vertex
            if(!vis[i * C + j]) return false;
    return true;
}
int main()
{
    while(~scanf("%d %d", &r, &c) && r != 0 && c != 0) {
        memset(sheet, 0, sizeof(sheet));
        memset(mSign, 0, sizeof(mSign));
        memset(vis, 0, sizeof(vis));
        memset(map, 0, sizeof(map));
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++) {
                scanf("%s", expre[i * C + j]);
                HandlePoint(expre[i * C + j], i * C + j);
            }
        if(Solve()) {
            printf(" ");
            for(int i = 0; i < c; i++)
                printf("%6d", i);
            printf("\n");
            for(int i = 0; i < r; i++) {
                printf("%c", i + 'A');
                for(int j = 0; j < c; j++)
                    printf("%6d", sheet[i * C + j]);
                printf("\n");
            }
        } else {
            for(int i = 0; i < r; i++)
                for(int j = 0; j < c; j++)
                    if(!vis[i * C + j]) \
                        printf("%c%d: %s\n", i + 'A', j, expre[i * C + j]);
        }
        printf("\n");
    }
    return 0;
}