#include <stdio.h>
const int maxn = 1000;
int n;
unsigned int ip[maxn];
void PrintIP(unsigned int x) {
    unsigned char t[4];
    for(int i = 0; i < 4; i++) {
        t[i] = x & (0x000000ff);
        x = x >> 8;
    }
    printf("%d.%d.%d.%d\n", t[3], t[2], t[1], t[0]);
}
int main() {
    while(scanf("%d\n", &n) != EOF) {
        for(int i = 0; i < n; i++) {
            unsigned char temp;
            ip[i] = 0;
            for(int j = 0; j < 3; j++) {
                scanf("%d.", &temp);
                ip[i] = (ip[i] + temp) << 8;
            }
            scanf("%d\n", &temp);
            ip[i] = (ip[i] + temp);
        }
        int i;
        unsigned int netIp = 0, netMask = 0;
        for(i = 31; i >= 0; i--) {
            //printf("i:%d\n",i);
            unsigned int mask = 1 << i;
            unsigned int t = ip[0] & mask, b = 1;
            for(int j = 0; j < n; j++)
                if((ip[j] & mask) != t) {
                    b = 0;
                    break;
                }
            if(!b) break;
            netIp += t;
            netMask += mask;
        }
        PrintIP(netIp);
        PrintIP(netMask);
    }
    return 0;
}